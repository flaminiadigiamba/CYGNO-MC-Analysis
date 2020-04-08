from ROOT import *
import os
import ConfigParser
import io

gROOT.SetBatch(True)

#### function to read config file
def readConfig(config_file_name,dict_bkg):
  config_file = open(config_file_name)
  for line in config_file:
    if not line.startswith("#"):
      key = line.split()[0]
      value = line.split()[1].split(":")
      dict_bkg[key] = value

#########   main  #####################

if __name__ == '__main__':

  
  f = []
  h = []
  h_NR = []
  lab = []
  color = [kAzure-1,kAzure+1,kTeal-9,kTeal-5,kMagenta-7,kPink-9,kViolet-6,kViolet-4,kBlue+3,kBlue+2,kGray+1,kGray+2,kGray+3]
  
  list_input = "lists/list4plot_AcrylicBox.txt"
  #list_input = "list_Shield2Activity_5Pb5Cu.txt"
  #list_input = "list_CameraBodyActivity_noshield.txt"
  #list_input = "list_CameraBodyActivity_shield.txt"
  rate = 0
  rate_NR = 0
  i=0

  #sample_config = """
  #[mysqld]
  #user = mysql
  #pid-file = /var/run/mysqld/mysqld.pid
  #skip-external-locking
  #old_passwords = 1
  #skip-bdb
  #skip-innodb
  #"""
  #config = ConfigParser.RawConfigParser(allow_no_value=True)
  #config.readfp(io.BytesIO(configPlot))
  
  # Settings with values are treated as before:
  #files = config.get("[40K]", "files")
 

  for line in open(list_input):
  #for line in 
      f.append(TFile(line.rstrip()))
      h.append(f[i].Get("h_edepDet_full_norm"))
      h_NR.append(f[i].Get("h_edepDet_NR_norm"))
      lab.append(os.path.basename(line.strip(".root\n").split("_")[0]))   
      rate += h[i].Integral(0,h[i].FindBin(20)-1)*h[i].GetBinWidth(1)*365*1.6
      rate_NR += h_NR[i].Integral(0,h_NR[i].FindBin(20)-1)*h_NR[i].GetBinWidth(1)*365*1.6
      print("rate of "+os.path.basename(line.strip(".root\n"))+"  = "+str(h[i].Integral(0,h[i].FindBin(20)-1)*h[i].GetBinWidth(1)*365*1.6)+" cts/yr")
      print("rate of NR of "+os.path.basename(line.strip(".root\n"))+"  = "+str(h_NR[i].Integral(0,h_NR[i].FindBin(20)-1)*h_NR[i].GetBinWidth(1)*365*1.6)+" cts/yr")
      i+=1
  
  h_tot = h[0].Clone("h_tot")
  for i in range(1,len(h)):
    h_tot.Add(h[i])
  h_tot.SetLineColor(4)
  h_tot.SetLineWidth(2)
  
  print("rate : "+str(rate)+" cts/yr")
  print("rate of NR : "+str(rate_NR)+" cts/yr")
  
  s = THStack()
  leg = TLegend(0.5,0.5,0.85,0.85)
  leg.SetFillColor(0)
  leg.SetFillStyle(0)
  leg.SetLineColor(0)
  leg.SetLineWidth(0)
  leg.SetBorderSize(0)
  leg.SetNColumns(2)
  s_NR = THStack()
  leg_NR = TLegend(0.5,0.6,0.85,0.85)
  leg_NR.SetFillColor(0)
  leg_NR.SetFillStyle(0)
  leg_NR.SetLineColor(0)
  leg_NR.SetLineWidth(0)
  leg_NR.SetBorderSize(0)
  leg_NR.SetNColumns(2)
  
  for i in range(0,len(h)):
      #h[i].SetLineColor(color[i])
      #h[i].SetFillColor(color[i])
      #h[i].SetLineColor(i)
      #h[i].SetFillColor(i)
      #h[i].SetFillStyle(1001)
      leg.AddEntry(h[i],lab[i],"f")
      s.Add(h[i],"HIST")
      leg_NR.AddEntry(h_NR[i],lab[i],"f")
      s_NR.Add(h_NR[i],"HIST")

  leg.AddEntry(h_tot, "Tot Bkg", "l" )
  
  #s.GetHistogram().GetXaxis().SetRangeUser(0,500)
  c = TCanvas("c","",700,600)
  c.cd()
  gStyle.SetPalette(58)
  
  c.SetLogy(1)
  s.Draw("PFCPLC")
  h_tot.Draw("hist same")
  s.GetXaxis().SetTitle("Energy deposit [keV]")
  s.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s.GetXaxis().SetRangeUser(0,500)
  s.SetMinimum(1)
  s.SetMaximum(50)
  leg.Draw()
  c.SaveAs("Background_AcrylicBox.pdf")
  #c.SaveAs("Background_Shield2Pb_5Pb5Cu.pdf")
  #c.SaveAs("Background_CameraBodyActivity_noshield.pdf")
  #c.SaveAs("Background_CameraBodyActivity_shield.pdf")
  
  c_NR = TCanvas("c_NR","",700,600)
  c_NR.cd()
  gStyle.SetPalette(70)
  
  c_NR.SetLogy(1)
  s_NR.Draw("PFCPLC")
  s_NR.GetXaxis().SetTitle("Energy deposit [keV]")
  s_NR.GetYaxis().SetTitle("Rate [cpd / kg / keV]")
  s_NR.GetXaxis().SetRangeUser(0,50)
  s_NR.SetMinimum(1e-15)
  s_NR.SetMaximum(1)
  leg_NR.Draw()
  c_NR.SaveAs("Background_AcrylicBox_NR.pdf")
  
