#!/bin/bash

# Welcome
echo "----------------------------------"
echo "Go Go Analyzer!"
echo ""

# Check that necesarry file structure existis
echo "Checking for valid directory structure..." 
echo ""
if [ ! -d Histos ]; then mkdir Histos; fi
if [ ! -d Histos/Nominal ]; then mkdir Histos/Nominal; fi
if [ ! -d Histos/JESup ]; then mkdir Histos/JESup; fi
if [ ! -d Histos/JESdown ]; then mkdir Histos/JESdown; fi

if [ ! -d Plots ]; then mkdir Plots; fi

# Create Histograms of all samples
echo "Creating Histograms..."
echo ""
root -l -b -q scanAllChains.C >& Histos/scanAllChains.log 

# For aMC@NLO samples, zero yields if final weight is negative
echo "Zeroing negative Yields..."
echo ""
. zeroOutNegativeYields.sh Histos/Nominal >& Histos/Nominal/zeroOutNegativeYields.log
. zeroOutNegativeYields.sh Histos/JESup >& Histos/JESup/zeroOutNegativeYields.log
. zeroOutNegativeYields.sh Histos/JESdown >& Histos/JESdown/zeroOutNegativeYields.log

# In case any sample needs additional x-section scaling
echo "Rescaling Samples..."
echo ""
root -l -b -q scaleSamples.C++ >& Histos/scaleSamples.log 

# Sum samples together
echo "Summing Samples..."
echo ""
. mergeStopBabies.sh >& Histos/mergeStopBabies.log

# Calculate Uncertainties
echo "Calculating Uncertainties..."
echo ""
root -l -b -q calcErrors.C++ >& Histos/Nominal/calcErrors.log

cd Histos/Nominal/
hadd -f histos__allBkg_25ns_summedErrors_v2.root histos__rare_25ns_summedErrors.root histos__WJets_25ns_summedErrors.root histos__DYJets_25ns_summedErrors.root histos__singleT_25ns_summedErrors.root histos__ttbar_25ns_summedErrors.root 
cd ../../

# Make plots
echo "Making Plots..."
echo ""
root -l -b -q plotMaker.C++ >& Plots/plotMaker.log

# Make tables
echo "Making Tables..."
echo ""
root -l -b -q tableMaker.C++ >& Plots/tableMaker.log

# nJets SFs
echo "Calculating nJets SF..."
echo ""
root -l -b -q nJets_SF_extractor.C++ >& Plots/nJets_SF_extractor.log

# Create pdfs of latex files
echo "Converting Tex to PDF"
echo ""
cd Plots/
for x in `/bin/ls *.tex`; do pdflatex $x; done
cd ../

# Done!
echo ""
echo "----------------------------------"
echo " Analysis Results Written To: "
echo "   Histos/ "
echo "   Plots/ " 
echo "---------------------------------"