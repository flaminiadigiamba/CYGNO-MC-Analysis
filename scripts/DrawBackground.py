from ROOT import *
import os
import ConfigParser
import io
import argparse

gROOT.SetBatch(True)

##### function to read config file
def readConfig(config_file_name,dict_bkg):
  config = ConfigParser.ConfigParser(allow_no_value=True)
  config.read(config_file_name)
  # Settings with values are treated as before:
  #print(config.sections())
  for i in range(0, len(config.sections())):
    files = config.get(config.sections()[i], "listfiles")
    dict_bkg[config.sections()[i]] = str(files).split()

#####
def create_histodict(dict_bkg,dict_h,histname):
  for key in dict_bkg:
    dict_h[key] = TH1F("hsum_"+key,"",600,0,120)
  for key in dict_bkg:
    val = dict_bkg[key]
    for i in range(0,len(val)):
      f = TFile.Open(val[i])
      h = f.Get(histname)
      print(val[i])
      h.Print()
      dict_h.get(key).Add(h)
      #dict_h[key].Print()


#####
def create_histodict_full(dict_bkg,dict_h,histname):
  for key in dict_bkg:
    dict_h[key] = TH1F("hsum_full_"+key,"",600,0,3000)
  for key in dict_bkg:
    val = dict_bkg[key]
    for i in range(0,len(val)):
      f = TFile.Open(val[i])
      h = f.Get(histname)
      dict_h.get(key).Add(h)
      #dict_h[key].Print()


#########   main  #####################

if __name__ == '__main__':


  usage = "usage : ..."
  print usage
  parser = argparse.ArgumentParser(description='Process options.')
  parser.add_argument("-i", type=str, dest="drawconf", default="config/DrawConfig_GEM.txt",
      help="Text file containing the files to plot",
      )
  parser.add_argument("--tag", type=str, dest="tag", default="",
      help="Output directory name",
      )
  
  args = parser.parse_args()
  print args 

  os.system("mkdir -p plots/"+args.tag)
  
  f = []
  h = []
  h_noNorm = []
  h_NR = []
  h_full = []
  h_full_NR = []
  lab = []
  labNR = []
  color = [kAzure-1,kAzure+1,kTeal-9,kTeal-5,kMagenta-7,kPink-9,kViolet-6,kViolet-4,kBlue+3,kBlue+2,kGray+1,kGray+2,kGray+3]
 
 
  #list_input = "lists/list4plot_Cathode.txt"
  #list_input = "lists/list4plot_GEM.txt"
  #list_input = "lists/list4plot_AcrylicBox.txt"
  #list_input = "list_Shield2Activity_5Pb5Cu.txt"
  #list_input = "list_CameraBodyActivity_noshield.txt"
  #list_input = "list_CameraBodyActivity_shield.txt"
  rate = 0
  rate_NR = 0

  dict_bkg = {}
  readConfig(args.drawconf,dict_bkg)
  #readConfig("config/DrawConfig_CameraBody_noshield.txt",dict_bkg)
  #readConfig("config/DrawConfig_GEM.txt",dict_bkg)
  #readConfig("config/DrawConfig_AcrylicBox.txt",dict_bkg)
  #print(dict_bkg.keys())
  #print(dict_bkg)

  dict_hbkg = {}
  dict_hbkg_noNorm = {}
  dict_hbkg_full = {}
  dict_hbkg_NR = {}
  dict_hbkg_full_NR = {}

  create_histodict(dict_bkg,dict_hbkg,"h_edepDet_norm")
  print("created norm")
  create_histodict(dict_bkg,dict_hbkg_noNorm,"h_edepDet")
  print("created no norm")
  create_histodict(dict_bkg,dict_hbkg_NR,"h_edepDet_NR_norm")
  print("created norm NR")
  create_histodict_full(dict_bkg,dict_hbkg_full,"h_edepDet_full_norm")
  print("created full norm")
  create_histodict_full(dict_bkg,dict_hbkg_full_NR,"h_edepDet_NR_full_norm")
  print("created full norm NR")
  #print(dict_hbkg)

  i=0
  #for line in open(list_input):
  #for line in 
  #    if not line.startswith('#'):
  #      f.append(TFile(line.rstrip()))
  #      #h.append(f[i].Get("h_edepDet_full_norm"))
  #      h.append(f[i].Get("h_edepDet_norm"))
  #      h_noNorm.append(f[i].Get("h_edepDet"))
  #      h_NR.append(f[i].Get("h_edepDet_NR_norm"))
  #      h_full.append(f[i].Get("h_edepDet_full_norm"))
  #      h_full_NR.append(f[i].Get("h_edepDet_NR_full_norm"))
  #      lab.append(os.path.basename(line.strip(".root\n").split("_")[0]))   
  for key in sorted(dict_hbkg, key = lambda key: dict_hbkg[key].Integral()):
    #print(key+"  "+str(i))
    lab.append(key)
    h.append(dict_hbkg[key])
    h_noNorm.append(dict_hbkg[key])
    h_full.append(dict_hbkg_full[key])
    rate += h[i].Integral(h[i].FindBin(1),h[i].FindBin(20)-1)*h[i].GetBinWidth(1)*365*1.6
    #print("rate [1-20] keV of "+os.path.basename(line.strip(".root\n"))+"  = "+str(h[i].Integral(h[i].FindBin(1),h[i].FindBin(20)-1)*h[i].GetBinWidth(1)*365*1.6)+" cts/yr")
    #print("rate [1-20] keV of NR of "+os.path.basename(line.strip(".root\n"))+"  = "+str(h_NR[i].Integral(h_NR[i].FindBin(1),h_NR[i].FindBin(20)-1)*h_NR[i].GetBinWidth(1)*365*1.6)+" cts/yr")
    print("rate [1-20] keV of "+key+"  = "+str(h[i].Integral(h[i].FindBin(1),h[i].FindBin(20)-1)*h[i].GetBinWidth(1)*365*1.6)+" cts/yr")
    if not (h[i].Integral() == 0):
      time_eq = (h_noNorm[i].Integral()/h[i].Integral())/(1.6*h[i].GetBinWidth(1))
    else:
      time_eq = -999
    #print("Equivalent time of "+os.path.basename(line.strip(".root\n"))+" simulation: "+str(time_eq)+" days")
    #print("Equivalent time of "+key+" simulation: "+str(time_eq)+" days")
    print("")
 
    i+=1

  i=0
  for key in sorted(dict_hbkg, key = lambda key: dict_hbkg_NR[key].Integral()):
    #print(key+"  "+str(i))
    labNR.append(key)
    h_NR.append(dict_hbkg_NR[key])
    h_full_NR.append(dict_hbkg_full_NR[key])
    rate_NR += h_NR[i].Integral(h_NR[i].FindBin(1),h_NR[i].FindBin(20)-1)*h_NR[i].GetBinWidth(1)*365*1.6
    print("rate [1-20] keV of NR of "+key+"  = "+str(h_NR[i].Integral(h_NR[i].FindBin(1),h_NR[i].FindBin(20)-1)*h_NR[i].GetBinWidth(1)*365*1.6)+" cts/yr")
 
    i+=1
  
  h_tot = h[0].Clone("h_tot")
  h_tot_NR = h_NR[0].Clone("h_tot_NR")
  h_full_tot = h_full[0].Clone("h_full_tot")
  h_full_tot_NR = h_full_NR[0].Clone("h_full_tot_NR")
  #print(len(h))
  for i in range(1,len(h)):
    h_tot.Add(h[i])
    h_tot_NR.Add(h_NR[i])
    h_full_tot.Add(h_full[i])
    h_full_tot_NR.Add(h_full_NR[i])

  h_tot.SetLineColor(4)
  h_tot.SetLineWidth(2)
  h_tot_NR.SetLineColor(2)
  h_tot_NR.SetLineWidth(2)
  h_full_tot.SetLineColor(4)
  h_full_tot.SetLineWidth(2)
  h_full_tot_NR.SetLineColor(2)
  h_full_tot_NR.SetLineWidth(2)
 
  print("rate [1-20] keV: "+str(rate)+" cts/yr")
  print("rate of NR [1-20] keV: "+str(rate_NR)+" cts/yr")
  
  s = THStack()
  s_full = THStack()
  leg = TLegend(0.5,0.65,0.85,0.85)
  leg.SetFillColor(0)
  leg.SetFillStyle(0)
  leg.SetLineColor(0)
  leg.SetLineWidth(0)
  leg.SetBorderSize(0)
  leg.SetNColumns(2)
  s_NR = THStack()
  s_full_NR = THStack()
  leg_NR = TLegend(0.5,0.65,0.85,0.85)
  leg_NR.SetFillColor(0)
  leg_NR.SetFillStyle(0)
  leg_NR.SetLineColor(0)
  leg_NR.SetLineWidth(0)
  leg_NR.SetBorderSize(0)
  leg_NR.SetNColumns(2)
  
  print("number of components: "+str(len(h)))
  for i in range(0,len(h)):
      #h[i].SetLineColor(color[i])
      #h[i].SetFillColor(color[i])
      #h_NR[i].SetLineColor(color[i])
      #h_NR[i].SetFillColor(color[i])
      #h_full[i].SetLineColor(color[i])
      #h_full[i].SetFillColor(color[i])
      #h_full_NR[i].SetLineColor(color[i])
      #h_full_NR[i].SetFillColor(color[i])
      #h[i].SetFillStyle(1001)
      leg.AddEntry(h[i],lab[i],"f")
      s.Add(h[i],"HIST")
      s_full.Add(h_full[i],"HIST")
      leg_NR.AddEntry(h_NR[i],labNR[i],"f")
      s_NR.Add(h_NR[i],"HIST")
      s_full_NR.Add(h_full_NR[i],"HIST")
 
  leg.AddEntry(h_tot, "Tot Bkg", "l" )
  leg.AddEntry(h_tot_NR, "Tot Bkg NR", "l" )
  leg_NR.AddEntry(h_tot_NR, "Tot Bkg NR", "l" )
  
  #s.GetHistogram().GetXaxis().SetRangeUser(0,500)
  c = TCanvas("c","",700,600)
  c.cd()
  gStyle.SetPalette(57)
  #gStyle.SetPalette(84)
 
  
  c.SetLogy(1)
  s.Draw("PFCPLC")
  #s.Draw("")
  h_tot.Draw("hist same")
  h_tot_NR.Draw("hist same")
  s.GetXaxis().SetTitle("Energy deposit [keV]")
  s.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s.GetXaxis().SetRangeUser(0,30)
  s.SetMinimum(1e-3)
  s.SetMaximum(1e5)
  leg.Draw()
  #c.SaveAs("Background_GEM_lowEne.pdf")
  #c.SaveAs("Background_AcrylicBox_lowEne.pdf")
  #c.SaveAs("Background_Shield2Pb_5Pb5Cu.pdf")
  #c.SaveAs("Background_CameraBody_noshield_lowEne.pdf")
  #c.SaveAs("Background_CameraBodyActivity_shield.pdf")
  c.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_lowEne.png")
  c.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_lowEne.pdf")
  c.Clear()
  gStyle.SetPalette(57)
  s_full.Draw("PFCPLC")
  #s_full.Draw("")
  h_full_tot.Draw("hist same")
  h_full_tot_NR.Draw("hist same")
  s_full.GetXaxis().SetTitle("Energy deposit [keV]")
  s_full.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s_full.GetXaxis().SetRangeUser(0,1000)
  s_full.SetMinimum(1e-2)
  s_full.SetMaximum(1e4)
  leg.Draw()
  #c.SaveAs("Background_CameraBody_noshield.pdf")
  #c.SaveAs("Background_GEM.pdf")
  #c.SaveAs("Background_AcrylicBox.pdf")
  c.SaveAs("plots/"+args.tag+"/Background_"+args.tag+".png")
  c.SaveAs("plots/"+args.tag+"/Background_"+args.tag+".pdf")
  
  c_NR = TCanvas("c_NR","",700,600)
  c_NR.cd()
  gStyle.SetPalette(70)
  
  c_NR.SetLogy(1)
  s_NR.Draw("PFCPLC")
  #s_NR.Draw("")
  s_NR.GetXaxis().SetTitle("Energy deposit [keV]")
  s_NR.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s_NR.GetXaxis().SetRangeUser(0,30)
  s_NR.SetMinimum(1e-4)
  s_NR.SetMaximum(1e3)
  h_tot_NR.Draw("hist same")
  leg_NR.Draw()
  #c_NR.SaveAs("Background_AcrylicBox_NR_lowEne.pdf")
  #c_NR.SaveAs("Background_GEM_NR_lowEne.pdf")
  c_NR.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_NR_lowEne.png")
  c_NR.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_NR_lowEne.pdf")
  c_NR.Clear()
  gStyle.SetPalette(70)
  s_full_NR.Draw("PFCPLC")
  #s_full_NR.Draw("")
  s_full_NR.GetXaxis().SetTitle("Energy deposit [keV]")
  s_full_NR.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s_full_NR.GetXaxis().SetRangeUser(0,1000)
  s_full_NR.SetMinimum(1e-4)
  s_full_NR.SetMaximum(1e3)
  h_full_tot_NR.Draw("hist same")
  leg_NR.Draw()
  c_NR.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_NR.pdf")
  c_NR.SaveAs("plots/"+args.tag+"/Background_"+args.tag+"_NR.png")
  #c_NR.SaveAs("Background_GEM_NR.pdf")
  #c_NR.SaveAs("Background_AcrylicBox_NR.pdf")
  
