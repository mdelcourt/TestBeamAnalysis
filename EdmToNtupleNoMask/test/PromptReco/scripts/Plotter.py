from ROOT import *
from optparse import OptionParser
import os

parser = OptionParser()
parser.add_option('-i',dest="fileIn",default="",metavar="FILE",help="input file")
parser.add_option('-o',dest="folderOut",default="",metavar="FILE",help="output folder")

(options, args) = parser.parse_args()
fileIn = options.fileIn
folderOut=options.folderOut
print "fileIn : %s"%fileIn
print "folderOut : %s"%folderOut
if not folderOut in os.listdir(folderOut.replace(folderOut.split("/")[-1],"")):
    print "Warning, the folder may not exist"
f = TFile(fileIn)

c=TCanvas()
StubPlot=f.Get("stubInfo")
StubPlot.SetStats(0)
StubPlot.Draw("colz text")
c.Print("%s/stubInfo.png"%folderOut)
for i in range(13):
    StubPlotTdc=f.Get("stubInfo_tdc%s"%i)
    StubPlotTdc.SetStats(0)
    StubPlotTdc.Draw("colz text")
    c.Print("%s/stubInfo_tdc%s.png"%(folderOut,i))

for i in range(4):
    h=f.Get("h%s"%i)
    h.Draw()
    c.Print("%s/clusters_%s.png"%(folderOut,i))

