

from ROOT import *
import csv,os

hName="Summary"
comment="Please don't edit this file."

def createLine(fName,keys):
    
    f = TFile(fName)
    h = f.Get(hName)
    if not h:
        print "Can't find hist in %s"%fName
        return([])
    results=[0 for k in keys]
    results[0]=fName
    
    i = 1
    while not h.GetXaxis().GetBinLabel(i)=='':
        hkey = h.GetXaxis().GetBinLabel(i)
        for j in range(len(keys)):
            if hkey==keys[j]:
                results[j]=h.GetBinContent(i)
                break
        i+=1
    return(results)

def getKeys(fName):
    f=TFile(fName)
    h=f.Get(hName)
    k=["fName"]
    if not h:
        print "Can't find hist in %s"%fName
        return([])
    i=1
    while not h.GetXaxis().GetBinLabel(i)=='':
        k.append(h.GetXaxis().GetBinLabel(i))
        i+=1
    return(k)

def createCSV(fList=[],csvName="test.csv"):
    fList.sort()
    header=[]   
    data=[]
#   Opening csv file
    csvFolder=csvName[:-len(csvName.split("/")[-1])]
    if csvFolder=="":csvFolder="."
    if csvName.split("/")[-1] in os.listdir(csvFolder):
        print "Found existing csv file... reading values..."
        with open(csvName,"rb") as csvFile:
            r = csv.reader(csvFile, delimiter=',', quotechar='|')
            lineCount=0
            for row in r:
                if lineCount<2:
                    header.append(row)
                else:
                    data.append(row)
                lineCount+=1
    else:
        print "No csv file found. Creating new one"
        header=[[],[]]

#   Check for keys
    keys=header[1]
    for f in fList:
        keys2 = getKeys(f)
        for k in keys2:
            if not k in keys:
                keys.append(k)

#   Check for run in list
    toRemove=[]
    for newRun in fList:
        for i in range(len(data)):
            if data[i][0]==newRun:
                print "Updating %s"%newRun
                data[i]=createLine(newRun,header[1])
                toRemove.append(newRun)
    for x in toRemove:
        fList.remove(x)
#   Append new runs
    for newRun in fList:
        print "Adding %s"%newRun
        data.append(createLine(newRun,header[1]))
#   Sort by run number
    
#   Save new CSV file
    with open(csvName,"wb") as csvFile:
        r=csv.writer(csvFile,delimiter=',', quotechar='|', quoting=csv.QUOTE_NONE)
        header=[[comment],keys]
        for line in header:
            r.writerow([i for i in line])
        for line in data:
            r.writerow([i for i in line])
    print "done..."


if __name__=="__main__":
    createCSV()
