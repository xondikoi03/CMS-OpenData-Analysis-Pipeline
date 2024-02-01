//C++
//Class: MasterAnalyzer
//Original Author: Raj Handique
//Created on: 4 January 2023

//include header files//

#include "MinimumBiasAnalyzer.h"

// -------- member functions ---------- //

//--------------------------------------------//
// This Function will collect the necessary   //
// information required from the AOD & AODSIM //
// files and put them in a Flat NTuple or a   //
// TTree - readable in ROOT                   //
//--------------------------------------------//

void 
MinimumBiasAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;

  Handle<reco::PFJetCollection> Jets;
  iEvent.getByLabel(InputTag("ak5PFJets"), Jets);

  Handle<reco::MuonCollection> recoMuons;
  iEvent.getByLabel(InputTag("muons"), recoMuons);

  Handle<reco::GsfElectronCollection> recoElectrons;
  iEvent.getByLabel(InputTag("gsfElectrons"), recoElectrons);

  Handle<reco::PhotonCollection> recoPhotons;
  iEvent.getByLabel(InputTag("photons"), recoPhotons);

  //--------------------- initialization of the arrays -------------------------//
  
  // Reco Jet //
  
  nJet=0;
  Jet_e.clear();
  Jet_pt.clear();
  Jet_eta.clear();
  Jet_phi.clear();
  Jet_mass.clear();
  Jet_area.clear();
  Jet_chEmEF.clear();
  Jet_chHEF.clear();
  Jet_neEmEF.clear();
  Jet_neHEF.clear();
  Jet_nConstituents.clear();

  // Reco Muon //
  
  nMuon=0;
  Muon_e.clear();
  Muon_pt.clear();
  Muon_eta.clear();
  Muon_phi.clear();
  Muon_mass.clear();
  Muon_pdgId.clear();
  Muon_charge.clear();
  Muon_px.clear();
  Muon_py.clear();
  Muon_pz.clear();
  
  // Reco Electron //

  nElectron=0;
  Electron_e.clear();
  Electron_pt.clear();
  Electron_eta.clear();
  Electron_phi.clear();
  Electron_mass.clear();
  Electron_pdgId.clear();
  Electron_charge.clear();
  Electron_px.clear();
  Electron_py.clear();
  Electron_pz.clear();
  
  // Reco Photons //

  nPhoton=0;
  Photon_e.clear();
  Photon_pt.clear();
  Photon_eta.clear();
  Photon_phi.clear();
  Photon_mass.clear();
  Photon_charge.clear();
  Photon_pdgId.clear();
  Photon_px.clear();
  Photon_py.clear();
  Photon_pz.clear();
  

  // Filling RecoJet Collection in the TTree (Flat NTuple)

  if(Jets.isValid()){
    
    for(reco::PFJetCollection::const_iterator rJet=Jets->begin(); rJet!=Jets->end(); rJet++){
      
      if(rJet->pt()>15){

	Jet_e.push_back(rJet->energy());
	Jet_pt.push_back(rJet->pt());	
	Jet_eta.push_back(rJet->eta());
	Jet_phi.push_back(rJet->phi());
	Jet_mass.push_back(rJet->mass());
	Jet_area.push_back(rJet->jetArea());
	Jet_chEmEF.push_back(rJet->chargedEmEnergyFraction());
	Jet_chHEF.push_back(rJet->chargedHadronEnergyFraction());
	Jet_neEmEF.push_back(rJet->neutralEmEnergyFraction());
	Jet_neHEF.push_back(rJet->neutralHadronEnergyFraction());
	Jet_nConstituents.push_back(rJet->nConstituents());
      }

      nJet = Jet_pt.size();
    }
  }

  // Filling RecoMu Collection in the TTree (Flat NTuple)

  if(recoMuons.isValid()){
    
    for(reco::MuonCollection::const_iterator rMuon=recoMuons->begin(); rMuon!=recoMuons->end(); rMuon++ ){
      if(rMuon->pt()>3){
	
	Muon_e.push_back(rMuon->energy());
	Muon_pt.push_back(rMuon->pt());
	Muon_eta.push_back(rMuon->eta());
	Muon_phi.push_back(rMuon->phi());
	Muon_mass.push_back(rMuon->mass());
	Muon_pdgId.push_back(rMuon->pdgId());
	Muon_charge.push_back(rMuon->charge());
        Muon_px.push_back(rMuon->px());
	Muon_py.push_back(rMuon->py());
	Muon_pz.push_back(rMuon->pz());
      }
      nMuon=Muon_pt.size();
    }
  }

  // Filling RecoEle Collection in the TTree (Flat NTuple)

  if(recoElectrons.isValid()){
    
    for(reco::GsfElectronCollection::const_iterator rElectron=recoElectrons->begin(); rElectron!=recoElectrons->end(); rElectron++){
      if(rElectron->pt()>3){
	
	Electron_e.push_back(rElectron->energy());
	Electron_pt.push_back(rElectron->pt());
	Electron_eta.push_back(rElectron->eta());
	Electron_phi.push_back(rElectron->phi());
	Electron_mass.push_back(rElectron->mass());
	Electron_pdgId.push_back(rElectron->pdgId());
	Electron_charge.push_back(rElectron->charge());
	Electron_px.push_back(rElectron->px());
	Electron_py.push_back(rElectron->py());
	Electron_pz.push_back(rElectron->pz());
      }
      nElectron=Electron_pt.size();
    }
  }
  
  // Filling RecoPho Collection in the TTree (Flat NTuple)

  if(recoPhotons.isValid()){
    
    for(reco::PhotonCollection::const_iterator rPhoton=recoPhotons->begin(); rPhoton!=recoPhotons->end(); rPhoton++){
      if(rPhoton->pt()>3){
	
	Photon_e.push_back(rPhoton->energy());
	Photon_pt.push_back(rPhoton->pt());
	Photon_eta.push_back(rPhoton->eta());
	Photon_phi.push_back(rPhoton->phi());
	Photon_mass.push_back(rPhoton->mass());
	Photon_pdgId.push_back(rPhoton->pdgId());
	Photon_charge.push_back(rPhoton->charge());
	Photon_px.push_back(rPhoton->px());
	Photon_py.push_back(rPhoton->py());
	Photon_pz.push_back(rPhoton->pz());
      }
      nPhoton=Photon_pt.size();
    }
  }
  
  mtree->Fill();
  return;
  
}

DEFINE_FWK_MODULE(MinimumBiasAnalyzer);
