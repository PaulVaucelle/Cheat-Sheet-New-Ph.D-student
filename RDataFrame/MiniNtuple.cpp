
#include <ROOT/RDataFrame.hxx>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.root> <output_file.root>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    ROOT::EnableImplicitMT(8); // Multi-threading
    ROOT::RDataFrame df("FlyingTop/ttree", input_file);
    TFile output(output_file.c_str(), "RECREATE");
//------No Filter---------//

auto hData_Good_PV = df.Histo1D({"hData_Good_PV", "Histogramme original;GoodPV;Counts", 2, 0, 2}, "tree_Good_PV");
auto hData_Filter = df.Histo1D({"hData_Filter", "Histogramme original;Filter;Counts", 2, 0, 2}, "tree_Filter");
auto hData_FilterSameSign = df.Histo1D({"hData_FilterSameSign", "Histogramme original;FilterSameSign;Counts", 2, 0, 2}, "tree_FilterSameSign");

hData_Good_PV->Write();
hData_Filter->Write();
hData_FilterSameSign->Write();

//-------tree_Filter-------//
 
auto filter_df = df.Filter("tree_Filter == true","Filtre simple");
auto hData_njetNOmu_Filter = filter_df.Histo1D({"hData_njetNOmu_Filter", "Histogramme original;nJetNomu;Counts", 15, 0, 15}, "tree_njetNOmu");
hData_njetNOmu_Filter->Write();

//------tree_FIlterSamSign-----//
auto filterSameSign_df = df.Filter("tree_FilterSameSign == true","Filtre simple");
auto hData_njetNOmu_FilterSameSign = filterSameSign_df.Histo1D({"hData_njetNOmu_FilterSameSign", "Histogramme original;nJetNomu;Counts", 15, 0, 15}, "tree_njetNOmu");
hData_njetNOmu_FilterSameSign->Write();

//-------Filtre Global--------//
    auto filtered_df = df.Filter("((tree_Filter == true || tree_FilterSameSign == true) && tree_njetNOmu > 0) ", "Filtre global combine");
   
    auto hData_nPV = filtered_df.Histo1D({"hData_nPV", "Histogramme filtre;nPV;Counts", 100, 0, 100}, "tree_nPV");
    hData_nPV->Write();

    auto hData_njetNOmu = filtered_df.Histo1D({"hData_njetNOmu", "Histogramme filtre;nJetNomu;Counts", 100, 0, 100}, "tree_njetNOmu");
    hData_njetNOmu->Write();

    auto hTk_MVA = filtered_df.Histo1D({"hTk_MVA", "Histogramme filtre;BDT score;Counts", 200, -1, 1}, "tree_track_MVAval");
    hTk_MVA->Write();

    auto hData_Hemi = filtered_df.Histo1D({"hData_Hemi", "Histogramme filtre;Hemi;Counts", 3, 0, 3}, "tree_Hemi");
    hData_Hemi->Write();

//--Vtx filter only for these two histos --//

    auto StepGE1_df = filtered_df.Filter("tree_Hemi_Vtx_step[0] >=1","Filtre au vertex");
    auto hData_Hemi_Vtx1_stepGE1 = StepGE1_df.Histo1D({"hData_Hemi_Vtx1_stepGE1", "Histogramme filtre;Hemi;Counts", 3, 0, 3}, "tree_Hemi");
    hData_Hemi_Vtx1_stepGE1->Write();

    // auto Step12_df = filtered_df.Filter("tree_Hemi_Vtx_step >= 1 && tree_Hemi_Vtx_step <= 2","Filtre au vertex tight");
    // auto hData_Hemi_step12 = Step12_df.Histo1D({"hData_Hemi_step12", "Histogramme filtre;Hemi;Counts", 3, 0, 3}, "tree_Hemi");
    // hData_Hemi_step12->Write();

//-- Renaming of the branches to match the other script that generaters minintuples
// auto renamed_df = filtered_df
//     .Define("minieventNumber", "eventNumber")
//     .Define("minilumiBlock", "lumiBlock")
//     .Define("minitree_LHE_Weights", "tree_LHE_Weights")
//     .Define("minitree_MCEvt_weight", "tree_MCEvt_weight")
//     .Define("minitree_only_gen_wt", "tree_only_gen_wt")
//     .Define("minitree_event_weight", "tree_event_weight")
//     .Define("minitree_genTop_Weight", "tree_genTop_Weight")
//     .Define("minitree_gen_top_pt", "tree_gen_top_pt")
//     .Define("minitree_gen_top_rw_pt", "tree_gen_top_rw_pt")
//     .Define("miniPUweight", "PUweight")
//     .Define("miniPUweight_Up", "PUweight_Up")
//     .Define("miniPUweight_Down", "PUweight_Down")
//     .Define("miniPrefweight", "Prefweight")
//     .Define("miniPU_events", "PU_events")
//     .Define("minitree_Filter", "tree_Filter")
//     .Define("minitree_FilterSameSign", "tree_FilterSameSign")
//     .Define("minitree_trigger_doublelepton", "tree_trigger_doublelepton")
//     .Define("minitree_trigger_singlelepton", "tree_trigger_singlelepton")
//     .Define("minitree_GenPVx", "tree_GenPVx")
//     .Define("minitree_GenPVy", "tree_GenPVy")
//     .Define("minitree_GenPVz", "tree_GenPVz")
//     .Define("minitree_smu_mass", "tree_smu_mass")
//     .Define("minitree_neu_mass", "tree_neu_mass")
//     .Define("minitree_neu_ctau", "tree_neu_ctau")
//     .Define("minitree_Good_PV", "tree_Good_PV")
//     .Define("minitree_nPV", "tree_nPV")
//     .Define("minitree_PV_x", "tree_PV_x")
//     .Define("minitree_PV_y", "tree_PV_y")
//     .Define("minitree_PV_z", "tree_PV_z")
//     .Define("minitree_PV_ez", "tree_PV_ez")
//     .Define("minitree_PV_NChi2", "tree_PV_NChi2")
//     .Define("minitree_PV_ndf", "tree_PV_ndf")
//     .Define("minitree_PFMet_et", "tree_PFMet_et")
//     .Define("minitree_PFMet_phi", "tree_PFMet_phi")
//     .Define("minitree_HT", "tree_HT")
//     .Define("minitree_TRACK_SIZE", "tree_TRACK_SIZE")
//     .Define("minitree_nTracks", "tree_nTracks")
//     .Define("minitree_nLostTracks", "tree_nLostTracks")
//     .Define("minitree_muon_GenRecoTriggerMatched", "tree_muon_GenRecoTriggerMatched")
//     .Define("minitree_all_nmu", "tree_all_nmu")
//     .Define("minitree_nmu", "tree_nmu")
//     .Define("minitree_LT", "tree_LT")
//     .Define("minitree_Mmumu", "tree_Mmumu")
//     .Define("minitree_MmumuSameSign", "tree_MmumuSameSign")
//     .Define("minitree_muon_isPrompt", "tree_muon_isPrompt")
//     .Define("minitree_muon_pt", "tree_muon_pt")
//     .Define("minitree_muon_SF", "tree_muon_SF")
//     .Define("minitree_muon_eta", "tree_muon_eta")
//     .Define("minitree_muon_phi", "tree_muon_phi")
//     .Define("minitree_muon_dxy", "tree_muon_dxy")
//     .Define("minitree_muon_dz", "tree_muon_dz")
//     .Define("minitree_muon_charge", "tree_muon_charge")
//     .Define("minitree_muon_correction", "tree_muon_correction")
//     .Define("minitree_muon_gen", "tree_muon_gen")
//     .Define("minitree_muon_dxyError", "tree_muon_dxyError")
//     .Define("minitree_muon_dzError", "tree_muon_dzError")
//     .Define("minitree_muon_isLoose", "tree_muon_isLoose")
//     .Define("minitree_muon_isMedium", "tree_muon_isMedium")
//     .Define("minitree_muon_isTight", "tree_muon_isTight")
//     .Define("minitree_muon_isGlobal", "tree_muon_isGlobal")
//     .Define("minitree_muon_PFIsoVeryLoose", "tree_muon_PFIsoVeryLoose")
//     .Define("minitree_muon_PFIsoLoose", "tree_muon_PFIsoLoose")
//     .Define("minitree_muon_PFIsoMedium", "tree_muon_PFIsoMedium")
//     .Define("minitree_muon_PFIsoTight", "tree_muon_PFIsoTight")
//     .Define("minitree_muon_TkIsoLoose", "tree_muon_TkIsoLoose")
//     .Define("minitree_muon_TkIsoTight", "tree_muon_TkIsoTight")
//     .Define("minitree_muon_MiniIsoLoose", "tree_muon_MiniIsoLoose")
//     .Define("minitree_muon_MiniIsoMedium", "tree_muon_MiniIsoMedium")
//     .Define("minitree_muon_MiniIsoTight", "tree_muon_MiniIsoTight")
//     .Define("minitree_lepton_leadingpt", "tree_lepton_leadingpt")
//     .Define("minitree_lepton_leadingpt2", "tree_lepton_leadingpt2")
//     .Define("minitree_lepton_leadingeta", "tree_lepton_leadingeta")
//     .Define("minitree_lepton_leadingeta2", "tree_lepton_leadingeta2")
//     .Define("minitree_lepton_leadingphi", "tree_lepton_leadingphi")
//     .Define("minitree_lepton_leadingphi2", "tree_lepton_leadingphi2")
//     .Define("minitree_lepton_lepton_dR", "tree_lepton_lepton_dR")
//     .Define("minitree_lepton_lepton_dPhi", "tree_lepton_lepton_dPhi")
//     .Define("minitree_lepton_lepton_dEta", "tree_lepton_lepton_dEta")
//     .Define("minitree_lepton_leadingdxy", "tree_lepton_leadingdxy")
//     .Define("minitree_lepton_leadingdxy2", "tree_lepton_leadingdxy2")
//     .Define("minitree_lepton_leadingdz", "tree_lepton_leadingdz")
//     .Define("minitree_lepton_leadingdz2", "tree_lepton_leadingdz2")
//     .Define("minitree_all_nel", "tree_all_nel")
//     .Define("minitree_electron_nEle", "tree_electron_nEle")
//     .Define("minitree_electron_isPrompt", "tree_electron_isPrompt")
//     .Define("minitree_electron_pt", "tree_electron_pt")
//     .Define("minitree_electron_eta", "tree_electron_eta")
//     .Define("minitree_electron_phi", "tree_electron_phi")
//     .Define("minitree_electron_charge", "tree_electron_charge")
//     .Define("minitree_electron_dxy", "tree_electron_dxy")
//     .Define("minitree_electron_dz", "tree_electron_dz")
//     .Define("minitree_electron_gen", "tree_electron_gen")
//     .Define("minitree_electron_energy", "tree_electron_energy")
//     .Define("minitree_electron_et", "tree_electron_et")
//     .Define("minitree_electron_ecal_trk_postcorr", "tree_electron_ecal_trk_postcorr")
//     .Define("minitree_electron_isoR4", "tree_electron_isoR4")
//     .Define("minitree_electron_IsLoose", "tree_electron_IsLoose")
//     .Define("minitree_electron_IsMedium", "tree_electron_IsMedium")
//     .Define("minitree_electron_IsTight", "tree_electron_IsTight")
//     .Define("minitree_njet", "tree_njet")
//     .Define("minitree_njetNOmu", "tree_njetNOmu")
//     .Define("minitree_jet_pt", "tree_jet_pt")
//     .Define("minitree_jet_eta", "tree_jet_eta")
//     .Define("minitree_jet_phi", "tree_jet_phi")
//     .Define("minitree_jet_HadronFlavour", "tree_jet_HadronFlavour")
//     .Define("minitree_jet_btag_DeepJet", "tree_jet_btag_DeepJet")
//     .Define("minitree_jet_E", "tree_jet_E")
//     .Define("minitree_jet_leadingpt", "tree_jet_leadingpt")
//     .Define("minitree_jet_leadingpt2", "tree_jet_leadingpt2")
//     .Define("minitree_jet_leadingeta", "tree_jet_leadingeta")
//     .Define("minitree_jet_leadingeta2", "tree_jet_leadingeta2")
//     .Define("minitree_jet_jet_dR", "tree_jet_jet_dR")
//     .Define("minitree_jet_jet_dPhi", "tree_jet_jet_dPhi")
//     .Define("minitree_jet_jet_dEta", "tree_jet_jet_dEta")
//     .Define("minitree_muon_jet_dRmin", "tree_muon_jet_dRmin")
//     .Define("minitree_muon_jet_dRmax", "tree_muon_jet_dRmax")
//     .Define("minitree_elemu_jet_dRmin", "tree_elemu_jet_dRmin")
//     .Define("minitree_elemu_jet_dRmax", "tree_elemu_jet_dRmax")
//     .Define("minitree_ele_jet_dRmin", "tree_ele_jet_dRmin")
//     .Define("minitree_ele_jet_dRmax", "tree_ele_jet_dRmax")
//     .Define("minitree_Evts_MVAval", "tree_Evts_MVAval")
//     .Define("minitree_Evts_MVAvalDY", "tree_Evts_MVAvalDY")
//     .Define("minitree_Evts_MVAvalTT", "tree_Evts_MVAvalTT")
//     .Define("minitree_nLLP", "tree_nLLP")
//     .Define("minitree_LLP", "tree_LLP")
//     .Define("minitree_LLP_pt", "tree_LLP_pt")
//     .Define("minitree_LLP_eta", "tree_LLP_eta")
//     .Define("minitree_LLP_phi", "tree_LLP_phi")
//     .Define("minitree_LLP_x", "tree_LLP_x")
//     .Define("minitree_LLP_y", "tree_LLP_y")
//     .Define("minitree_LLP_z", "tree_LLP_z")
//     .Define("minitree_LLP_r", "tree_LLP_r")
//     .Define("minitree_LLP_dist", "tree_LLP_dist")
//     .Define("minitree_LLP_nTrks", "tree_LLP_nTrks")
//     .Define("minitree_LLP12_dR", "tree_LLP12_dR")
//     .Define("minitree_LLP12_deta", "tree_LLP12_deta")
//     .Define("minitree_LLP12_dphi", "tree_LLP12_dphi")
//     .Define("minitree_LLP_Mass", "tree_LLP_Mass")
//     .Define("minitree_Hemi", "tree_Hemi")
//     .Define("minitree_Hemi_njet", "tree_Hemi_njet")
//     .Define("minitree_Hemi_njet_nomu", "tree_Hemi_njet_nomu")
//     .Define("minitree_Hemi_pt", "tree_Hemi_pt")
//     .Define("minitree_Hemi_eta", "tree_Hemi_eta")
//     .Define("minitree_Hemi_phi", "tree_Hemi_phi")
//     .Define("minitree_Hemi_nTrks", "tree_Hemi_nTrks")
//     .Define("minitree_Hemi_nTrks_sig", "tree_Hemi_nTrks_sig")
//     .Define("minitree_Hemi_nTrks_bad", "tree_Hemi_nTrks_bad")
//     .Define("minitree_Hemi_mass", "tree_Hemi_mass")
//     .Define("minitree_HemiMu_mass", "tree_HemiMu_mass")
//     .Define("minitree_HemiMu_pt", "tree_HemiMu_pt")
//     .Define("minitree_HemiMu_dR", "tree_HemiMu_dR")
//     .Define("minitree_HemiMuOp_mass", "tree_HemiMuOp_mass")
//     .Define("minitree_HemiMuOp_pt", "tree_HemiMuOp_pt")
//     .Define("minitree_HemiMuOp_dR", "tree_HemiMuOp_dR")
//     .Define("minitree_Hemi_dR12", "tree_Hemi_dR12")
//     .Define("minitree_Hemi_LLP", "tree_Hemi_LLP")
//     .Define("minitree_Hemi_LLP_pt", "tree_Hemi_LLP_pt")
//     .Define("minitree_Hemi_LLP_eta", "tree_Hemi_LLP_eta")
//     .Define("minitree_Hemi_LLP_phi", "tree_Hemi_LLP_phi")
//     .Define("minitree_Hemi_LLP_dist", "tree_Hemi_LLP_dist")
//     .Define("minitree_Hemi_LLP_x", "tree_Hemi_LLP_x")
//     .Define("minitree_Hemi_LLP_y", "tree_Hemi_LLP_y")
//     .Define("minitree_Hemi_LLP_z", "tree_Hemi_LLP_z")
//     .Define("minitree_Hemi_LLP_dR", "tree_Hemi_LLP_dR")
//     .Define("minitree_Hemi_LLP_mother", "tree_Hemi_LLP_mother")
//     .Define("minitree_Hemi_LLP_Vtx_dx", "tree_Hemi_LLP_Vtx_dx")
//     .Define("minitree_Hemi_LLP_Vtx_dy", "tree_Hemi_LLP_Vtx_dy")
//     .Define("minitree_Hemi_LLP_Vtx_dz", "tree_Hemi_LLP_Vtx_dz")
//     .Define("minitree_Hemi_LLP_Vtx_dr", "tree_Hemi_LLP_Vtx_dr")
//     .Define("minitree_Hemi_LLP_muOK_dR", "tree_Hemi_LLP_muOK_dR")
//     .Define("minitree_Hemi_LLP_muOK_pt", "tree_Hemi_LLP_muOK_pt")
//     .Define("minitree_Hemi_LLP_muOK_mass", "tree_Hemi_LLP_muOK_mass")
//     .Define("minitree_Hemi_LLP_muNO_dR", "tree_Hemi_LLP_muNO_dR")
//     .Define("minitree_Hemi_LLP_muNO_pt", "tree_Hemi_LLP_muNO_pt")
//     .Define("minitree_Hemi_LLP_muNO_mass", "tree_Hemi_LLP_muNO_mass")
//     .Define("minitree_Hemi_LLP_dR12", "tree_Hemi_LLP_dR12")
//     .Define("minitree_Hemi_LLP_ping", "tree_Hemi_LLP_ping")
//     .Define("minitree_event_LLP_ping", "tree_event_LLP_ping")
//     .Define("minitree_Hemi_Vtx_step", "tree_Hemi_Vtx_step")
//     .Define("minitree_Hemi_Vtx_isTight", "tree_Hemi_Vtx_isTight")
//     .Define("minitree_Hemi_Vtx_NChi2", "tree_Hemi_Vtx_NChi2")
//     .Define("minitree_Hemi_Vtx_nTrks", "tree_Hemi_Vtx_nTrks")
//     .Define("minitree_Hemi_Vtx_nTrks_sig", "tree_Hemi_Vtx_nTrks_sig")
//     .Define("minitree_Hemi_Vtx_nTrks_bad", "tree_Hemi_Vtx_nTrks_bad")
//     .Define("minitree_Hemi_Vtx_x", "tree_Hemi_Vtx_x")
//     .Define("minitree_Hemi_Vtx_y", "tree_Hemi_Vtx_y")
//     .Define("minitree_Hemi_Vtx_z", "tree_Hemi_Vtx_z")
//     .Define("minitree_Hemi_Vtx_r", "tree_Hemi_Vtx_r")
//     .Define("minitree_Hemi_Vtx_dR", "tree_Hemi_Vtx_dR")
//     .Define("minitree_Hemi_Vtx_SumtrackWeight", "tree_Hemi_Vtx_SumtrackWeight")
//     .Define("minitree_Hemi_Vtx_track_MeanDCA_d", "tree_Hemi_Vtx_track_MeanDCA_d")
//     .Define("minitree_Hemi_Vtx_Mass", "tree_Hemi_Vtx_Mass")
//     .Define("minitree_Hemi_Vtx_dist", "tree_Hemi_Vtx_dist")
//     .Define("minitree_event_nVtx", "tree_event_nVtx")
//     .Define("minitree_event_Vtx_Vtx_dr", "tree_event_Vtx_Vtx_dr")
//     .Define("minitree_event_Vtx_Vtx_dz", "tree_event_Vtx_Vtx_dz")
//     .Define("minitree_event_Vtx_Vtx_dd", "tree_event_Vtx_Vtx_dd")
//     .Define("minitree_event_Vtx_Vtx_reldd", "tree_event_Vtx_Vtx_reldd")
//     .Define("minitree_event_Vtx_Vtx_dR", "tree_event_Vtx_Vtx_dR")
//     .Define("minitree_event_Vtx_Vtx_step", "tree_event_Vtx_Vtx_step")
//     .Define("minitree_Hemi_SecLLP", "tree_Hemi_SecLLP")
//     .Define("minitree_Hemi_LLP_SecVtx_dz", "tree_Hemi_LLP_SecVtx_dz")
//     .Define("minitree_Hemi_LLP_SecVtx_dr", "tree_Hemi_LLP_SecVtx_dr")
//     .Define("minitree_Hemi_SecLLP_ping", "tree_Hemi_SecLLP_ping")
//     .Define("minitree_event_SecLLP_ping", "tree_event_SecLLP_ping")
//     .Define("minitree_Hemi_SecVtx", "tree_Hemi_SecVtx")
//     .Define("minitree_Hemi_SecVtx_step", "tree_Hemi_SecVtx_step")
//     .Define("minitree_Hemi_SecVtx_x", "tree_Hemi_SecVtx_x")
//     .Define("minitree_Hemi_SecVtx_y", "tree_Hemi_SecVtx_y")
//     .Define("minitree_Hemi_SecVtx_z", "tree_Hemi_SecVtx_z")
//     .Define("minitree_Hemi_SecVtx_r", "tree_Hemi_SecVtx_r")
//     .Define("minitree_Hemi_SecVtx_dR", "tree_Hemi_SecVtx_dR")
//     .Define("minitree_Hemi_SecVtx_nTrks", "tree_Hemi_SecVtx_nTrks")
//     .Define("minitree_Hemi_SecVtx_NChi2", "tree_Hemi_SecVtx_NChi2")
//     .Define("minitree_Hemi_SecVtx_dist", "tree_Hemi_SecVtx_dist")
//     .Define("minitree_Hemi_SecVtx_track_MeanDCA_d", "tree_Hemi_SecVtx_track_MeanDCA_d")
//     .Define("minitree_Hemi_SecVtx_SumtrackWeight", "tree_Hemi_SecVtx_SumtrackWeight")
//     .Define("minitree_Hemi_SecVtx_Mass", "tree_Hemi_SecVtx_Mass")
//     .Define("minitree_event_MergedVtx_Vtx_dr", "tree_event_MergedVtx_Vtx_dr")
//     .Define("minitree_event_MergedVtx_Vtx_dz", "tree_event_MergedVtx_Vtx_dz")
//     .Define("minitree_event_MergedVtx_Vtx_dd", "tree_event_MergedVtx_Vtx_dd")
//     .Define("minitree_event_MergedVtx_Vtx_reldd", "tree_event_MergedVtx_Vtx_reldd")
//     .Define("minitree_event_MergedVtx_Vtx_dR", "tree_event_MergedVtx_Vtx_dR")
//     .Define("minitree_event_MergedVtx_Vtx_step", "tree_event_MergedVtx_Vtx_step")
//     .Define("minitree_Hemi_Vtx_BDT_nTrks", "tree_Hemi_Vtx_BDT_nTrks")
//     .Define("minitree_Hemi_Vtx_BDT_NChi2", "tree_Hemi_Vtx_BDT_NChi2")
//     .Define("minitree_Hemi_Vtx_BDT_step", "tree_Hemi_Vtx_BDT_step")
//     .Define("minitree_Hemi_Vtx_BDT_STW", "tree_Hemi_Vtx_BDT_STW")
//     .Define("minitree_Hemi_Vtx_BDT_Mass", "tree_Hemi_Vtx_BDT_Mass")
//     .Define("minitree_Hemi_Vtx_BDT_HMass", "tree_Hemi_Vtx_BDT_HMass")
//     .Define("minitree_Hemi_Vtx_BDT_ntrk10", "tree_Hemi_Vtx_BDT_ntrk10")
//     .Define("minitree_Hemi_Vtx_BDT_ntrk20", "tree_Hemi_Vtx_BDT_ntrk20")
//     .Define("minitree_Hemi_Vtx_BDT_MeanDCA", "tree_Hemi_Vtx_BDT_MeanDCA")
//     .Define("minitree_Hemi_Vtx_MVAval_Loose", "tree_Hemi_Vtx_MVAval_Loose")
//     .Define("minitree_Hemi_Vtx_MVAval_Tight", "tree_Hemi_Vtx_MVAval_Tight")
//     .Define("miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v")
//     .Define("miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v")
//     .Define("miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v")
//     .Define("miniHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")
//     .Define("miniHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")
//     .Define("miniHLT_Ele27_WPTight_Gsf_v", "HLT_Ele27_WPTight_Gsf_v")
//     .Define("miniHLT_Ele32_WPTight_Gsf_v", "HLT_Ele32_WPTight_Gsf_v")
//     .Define("miniHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")
//     .Define("miniHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_PFMET120_PFMHT120_IDTight_v", "HLT_PFMET120_PFMHT120_IDTight_v")
//     .Define("miniHLT_PFMET120_PFMHT120_IDTight_PFHT60_v", "HLT_PFMET120_PFMHT120_IDTight_PFHT60_v")
//     .Define("miniHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v", "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v")
//     .Define("miniHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v", "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")
//     .Define("miniHLT_PFMET250_HBHECleaned_v", "HLT_PFMET250_HBHECleaned_v")
//     .Define("miniHLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v", "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v")
//     .Define("miniHLT_IsoMu24_v", "HLT_IsoMu24_v")
//     .Define("miniHLT_IsoMu27_v", "HLT_IsoMu27_v")
//     .Define("miniHLT_IsoTkMu24_v", "HLT_IsoTkMu24_v")
//     .Define("miniHLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v", "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v")
//     .Define("miniHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v")
//     .Define("miniHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

//     renamed_df.Snapshot("ttree", output_file, {"minieventNumber", "minilumiBlock", "minitree_LHE_Weights", "minitree_MCEvt_weight", "minitree_only_gen_wt", "minitree_event_weight", "minitree_genTop_Weight", "minitree_gen_top_pt", "minitree_gen_top_rw_pt", "miniPUweight", "miniPUweight_Up", "miniPUweight_Down", "miniPrefweight", "miniPU_events", "minitree_Filter", "minitree_FilterSameSign", "minitree_trigger_doublelepton", "minitree_trigger_singlelepton", "minitree_GenPVx", "minitree_GenPVy", "minitree_GenPVz", "minitree_smu_mass", "minitree_neu_mass", "minitree_neu_ctau", "minitree_Good_PV", "minitree_nPV", "minitree_PV_x", "minitree_PV_y", "minitree_PV_z", "minitree_PV_ez", "minitree_PV_NChi2", "minitree_PV_ndf", "minitree_PFMet_et", "minitree_PFMet_phi", "minitree_HT", "minitree_TRACK_SIZE", "minitree_nTracks", "minitree_nLostTracks", "minitree_muon_GenRecoTriggerMatched", "minitree_all_nmu", "minitree_nmu", "minitree_LT", "minitree_Mmumu", "minitree_MmumuSameSign", "minitree_muon_isPrompt", "minitree_muon_pt", "minitree_muon_SF", "minitree_muon_eta", "minitree_muon_phi", "minitree_muon_dxy", "minitree_muon_dz", "minitree_muon_charge", "minitree_muon_correction", "minitree_muon_gen", "minitree_muon_dxyError", "minitree_muon_dzError", "minitree_muon_isLoose", "minitree_muon_isMedium", "minitree_muon_isTight", "minitree_muon_isGlobal", "minitree_muon_PFIsoVeryLoose", "minitree_muon_PFIsoLoose", "minitree_muon_PFIsoMedium", "minitree_muon_PFIsoTight", "minitree_muon_TkIsoLoose", "minitree_muon_TkIsoTight", "minitree_muon_MiniIsoLoose", "minitree_muon_MiniIsoMedium", "minitree_muon_MiniIsoTight", "minitree_lepton_leadingpt", "minitree_lepton_leadingpt2", "minitree_lepton_leadingeta", "minitree_lepton_leadingeta2", "minitree_lepton_leadingphi", "minitree_lepton_leadingphi2", "minitree_lepton_lepton_dR", "minitree_lepton_lepton_dPhi", "minitree_lepton_lepton_dEta", "minitree_lepton_leadingdxy", "minitree_lepton_leadingdxy2", "minitree_lepton_leadingdz", "minitree_lepton_leadingdz2", "minitree_all_nel", "minitree_electron_nEle", "minitree_electron_isPrompt", "minitree_electron_pt", "minitree_electron_eta", "minitree_electron_phi", "minitree_electron_charge", "minitree_electron_dxy", "minitree_electron_dz", "minitree_electron_gen", "minitree_electron_energy", "minitree_electron_et", "minitree_electron_ecal_trk_postcorr", "minitree_electron_isoR4", "minitree_electron_IsLoose", "minitree_electron_IsMedium", "minitree_electron_IsTight", "minitree_njet", "minitree_njetNOmu", "minitree_jet_pt", "minitree_jet_eta", "minitree_jet_phi", "minitree_jet_HadronFlavour", "minitree_jet_btag_DeepJet", "minitree_jet_E", "minitree_jet_leadingpt", "minitree_jet_leadingpt2", "minitree_jet_leadingeta", "minitree_jet_leadingeta2", "minitree_jet_jet_dR", "minitree_jet_jet_dPhi", "minitree_jet_jet_dEta", "minitree_muon_jet_dRmin", "minitree_muon_jet_dRmax", "minitree_elemu_jet_dRmin", "minitree_elemu_jet_dRmax", "minitree_ele_jet_dRmin", "minitree_ele_jet_dRmax", "minitree_Evts_MVAval", "minitree_Evts_MVAvalDY", "minitree_Evts_MVAvalTT", "minitree_nLLP", "minitree_LLP", "minitree_LLP_pt", "minitree_LLP_eta", "minitree_LLP_phi", "minitree_LLP_x", "minitree_LLP_y", "minitree_LLP_z", "minitree_LLP_r", "minitree_LLP_dist", "minitree_LLP_nTrks", "minitree_LLP12_dR", "minitree_LLP12_deta", "minitree_LLP12_dphi", "minitree_LLP_Mass", "minitree_Hemi", "minitree_Hemi_njet", "minitree_Hemi_njet_nomu", "minitree_Hemi_pt", "minitree_Hemi_eta", "minitree_Hemi_phi", "minitree_Hemi_nTrks", "minitree_Hemi_nTrks_sig", "minitree_Hemi_nTrks_bad", "minitree_Hemi_mass", "minitree_HemiMu_mass", "minitree_HemiMu_pt", "minitree_HemiMu_dR", "minitree_HemiMuOp_mass", "minitree_HemiMuOp_pt", "minitree_HemiMuOp_dR", "minitree_Hemi_dR12", "minitree_Hemi_LLP", "minitree_Hemi_LLP_pt", "minitree_Hemi_LLP_eta", "minitree_Hemi_LLP_phi", "minitree_Hemi_LLP_dist", "minitree_Hemi_LLP_x", "minitree_Hemi_LLP_y", "minitree_Hemi_LLP_z", "minitree_Hemi_LLP_dR", "minitree_Hemi_LLP_mother", "minitree_Hemi_LLP_Vtx_dx", "minitree_Hemi_LLP_Vtx_dy", "minitree_Hemi_LLP_Vtx_dz", "minitree_Hemi_LLP_Vtx_dr", "minitree_Hemi_LLP_muOK_dR", "minitree_Hemi_LLP_muOK_pt", "minitree_Hemi_LLP_muOK_mass", "minitree_Hemi_LLP_muNO_dR", "minitree_Hemi_LLP_muNO_pt", "minitree_Hemi_LLP_muNO_mass", "minitree_Hemi_LLP_dR12", "minitree_Hemi_LLP_ping", "minitree_event_LLP_ping", "minitree_Hemi_Vtx_step", "minitree_Hemi_Vtx_isTight", "minitree_Hemi_Vtx_NChi2", "minitree_Hemi_Vtx_nTrks", "minitree_Hemi_Vtx_nTrks_sig", "minitree_Hemi_Vtx_nTrks_bad", "minitree_Hemi_Vtx_x", "minitree_Hemi_Vtx_y", "minitree_Hemi_Vtx_z", "minitree_Hemi_Vtx_r", "minitree_Hemi_Vtx_dR", "minitree_Hemi_Vtx_SumtrackWeight", "minitree_Hemi_Vtx_track_MeanDCA_d", "minitree_Hemi_Vtx_Mass", "minitree_Hemi_Vtx_dist", "minitree_event_nVtx", "minitree_event_Vtx_Vtx_dr", "minitree_event_Vtx_Vtx_dz", "minitree_event_Vtx_Vtx_dd", "minitree_event_Vtx_Vtx_reldd", "minitree_event_Vtx_Vtx_dR", "minitree_event_Vtx_Vtx_step", "minitree_Hemi_SecLLP", "minitree_Hemi_LLP_SecVtx_dz", "minitree_Hemi_LLP_SecVtx_dr", "minitree_Hemi_SecLLP_ping", "minitree_event_SecLLP_ping", "minitree_Hemi_SecVtx", "minitree_Hemi_SecVtx_step", "minitree_Hemi_SecVtx_x", "minitree_Hemi_SecVtx_y", "minitree_Hemi_SecVtx_z", "minitree_Hemi_SecVtx_r", "minitree_Hemi_SecVtx_dR", "minitree_Hemi_SecVtx_nTrks", "minitree_Hemi_SecVtx_NChi2", "minitree_Hemi_SecVtx_dist", "minitree_Hemi_SecVtx_track_MeanDCA_d", "minitree_Hemi_SecVtx_SumtrackWeight", "minitree_Hemi_SecVtx_Mass", "minitree_event_MergedVtx_Vtx_dr", "minitree_event_MergedVtx_Vtx_dz", "minitree_event_MergedVtx_Vtx_dd", "minitree_event_MergedVtx_Vtx_reldd", "minitree_event_MergedVtx_Vtx_dR", "minitree_event_MergedVtx_Vtx_step", "minitree_Hemi_Vtx_BDT_nTrks", "minitree_Hemi_Vtx_BDT_NChi2", "minitree_Hemi_Vtx_BDT_step", "minitree_Hemi_Vtx_BDT_STW", "minitree_Hemi_Vtx_BDT_Mass", "minitree_Hemi_Vtx_BDT_HMass", "minitree_Hemi_Vtx_BDT_ntrk10", "minitree_Hemi_Vtx_BDT_ntrk20", "minitree_Hemi_Vtx_BDT_MeanDCA", "minitree_Hemi_Vtx_MVAval_Loose", "minitree_Hemi_Vtx_MVAval_Tight", "miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v", "miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v", "miniHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v", "miniHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", "miniHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", "miniHLT_Ele27_WPTight_Gsf_v", "miniHLT_Ele32_WPTight_Gsf_v", "miniHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", "miniHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_PFMET120_PFMHT120_IDTight_v", "miniHLT_PFMET120_PFMHT120_IDTight_PFHT60_v", "miniHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v", "miniHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v", "miniHLT_PFMET250_HBHECleaned_v", "miniHLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v", "miniHLT_IsoMu24_v", "miniHLT_IsoMu27_v", "miniHLT_IsoTkMu24_v", "miniHLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v", "miniHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v", "miniHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"});

std::cout << "Analyse terminee. TTree sauvegarde dans " << output_file << std::endl;

    return 0;
}
