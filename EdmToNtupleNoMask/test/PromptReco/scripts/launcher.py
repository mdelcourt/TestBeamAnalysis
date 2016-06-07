import os,sys,time
import commands
from optparse import OptionParser
parser = OptionParser()
parser.add_option("-s", "--step", dest="step", default="all",
                  help="Step")
parser.add_option("-f","--force",dest="force",action="store_true",help="Rerun all files")
parser.add_option("-m","--min",dest="runMin",default="100",help="Rerun all files")
parser.add_option("-M","--Max",dest="runMax",default="-1",help="Rerun all files")

(options, args) = parser.parse_args()
PWD = commands.getstatusoutput('pwd')[1]
WD="/home/xtaldaq/test_unpacker/CMSSW_6_2_0_SLHC16/src/TestBeamAnalysis/EdmToNtupleNoMask/test/PromptReco"
NAS="/cmsuptrackernas/PromptRecoData"
edmDir = NAS+"/unpackerOutput" 
treeDir=NAS+"/tree"
histDir=NAS+"/hist"
pngDir=NAS+"/png"
csvOutputFile=NAS+"/summary.csv"

env = "source /home/xtaldaq/scripts/cmssw.sh; cd %s; eval `scramv1 runtime -sh`;" %WD
nMin = int(options.runMin)-1
nMax = int(options.runMax)
step = options.step.lower()

if not step in ["all","tree","plot","csv"]:
    print "'%s' is an invalid step"% step
    sys.exit()
forceReprocess = options.force
if forceReprocess:
    print "Will reprocess all files."
print "Getting list of files to process..."

edmLs = os.listdir(edmDir)
treeLs = os.listdir(treeDir)
histLs = os.listdir(histDir)

treeEnd="_TREE.root"
histEnd="_HIST.root"

toProcess=[]
origin = []


if step == "all":
    origin = edmLs
    end=".root"
elif step == "tree":
    origin = treeLs
    end=treeEnd
elif step== "plot":
    origin = histLs
    end = histEnd
elif step== "csv":
    origin = histLs
    end = histEnd
for f in origin:
    if not f.replace(end,histEnd) in histLs or forceReprocess:
        if".root" in f[-6:] and int(f.split(".")[1])>nMin and (nMax<0 or int(f.split(".")[1])<nMax):
            toProcess.append(f)
#toProcess= ["USC.00000108.0001.A.storageManager.00.0000.root"]
            print f

if step in ["all","tree"] and len(toProcess)>0:
    print "###### Compiling hist producer"
    os.system(env+"cd scripts; root -l -b -q PromptReco.C+ >>log.txt 2>&1")
    if "PromptReco_C.so" in os.listdir(WD+"/scripts"):
        print "done"
    else:
        print "Compilation failed. View scripts/log.txt for details"
        sys.exit()

for fId in range(len(toProcess)):
    f=toProcess[fId]
    print "####### Processing %s (%s/%s)"%(f,fId+1,len(toProcess))
    if step =="all":
        print "@@@ Running Tree producer"
        cmd = env+"cmsRun scripts/treeMaker_cfg.py %s %s"%(edmDir+"/"+f,treeDir+"/"+f.replace(".root",treeEnd))
        print cmd
        os.system(cmd)
        f=f.replace(".root",treeEnd)
    if step in ["all","tree"]:
        print "@@@ Running hist producer"
        cmd=env+"cd scripts; echo 'gROOT->LoadMacro(\"PromptReco_C.so\"); PromptReco(\"%s\",\"%s\"); gSystem->Exit(0);' | root -b -l "%(treeDir+"/"+f,histDir+"/"+f.replace(treeEnd,histEnd))
        print cmd
        os.system(cmd)
        f=f.replace(treeEnd,histEnd)
    if step in ["all","tree","plot"]:
        print "@@@ Running Plotter.py"
        folderName=pngDir+"/"+f.replace(histEnd,"")
        if not folderName.split("/")[-1] in os.listdir(folderName[:-len(folderName.split("/")[-1])]):
            print "Creating new directory..."
            os.system("mkdir %s"%folderName)
        if not os.path.isdir(folderName):
            print "Error, %s is not a directory !"%folderName
        else:
            cmd=env+"cd scripts; python -b Plotter.py -i %s -o %s"%(histDir+"/"+f,folderName)
            print cmd
            os.system(cmd)
if step in ["all","tree","csv","plot"] and len(toProcess)>0:
    import scripts.CSVbuilder
    print "@@@Running CSV maker"
    toProcess.sort()
    print toProcess
    csvFiles=[]
    for fName in toProcess:
        csvFiles.append(histDir+"/"+fName.replace(end,histEnd))
    if not csvFiles==[]:
        scripts.CSVbuilder.createCSV(csvFiles,csvOutputFile)
    else:
        print "No new files to add to csv"
os.system("cd %s"%PWD)
