python GenerateMiniCode.py // to generate the cpp file with all your branches => the ouput ccp file will be the RDataframe setup to run on your Ntuples 
g++ -o analysis <name_of_gerenrated_file>.cpp $(root-config --cflags --libs) -lROOTDataFrame
./analysis <your_file>.root filtered_output.root
