#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int main(int argc, char** argv)
{

  if (argc != 2) //checking if filepath was entered. If no filepath given, program ends
  {
    cout << "Please run again and include the filepath" << endl;
    return 0;
  }

  ifstream textFile(argv[1]);

  ofstream myFile;
  myFile.open("travis.out");
  myFile << "Name: Travis Mayer" << endl;
  myFile << "Student ID: 002273275" << endl;

  while (true)
  {
    if (textFile.is_open() && textFile.good()) //checks if file is opened and readable and writable and other state flags
    {
      string line = ""; //lines from file
      int numLines = 0, sum = 0;
      double mean = 0, variance = 0, standardDeviation = 0;
      double rProbA = 0, rProbC = 0, rProbT = 0, rProbG = 0, c = 0, distribution = 0;

      while (getline(textFile, line))
      {
        sum += line.size();
        numLines++;
      }
      mean = sum / (double)numLines; //mean calculated
      textFile.clear();
      textFile.seekg(0, textFile.beg); //resetting the file location to beginning as mean was needed to find variance

      while (getline(textFile, line))
      {
        variance += pow((line.size() - mean), 2);

        for(int i = 0; i < line.size(); ++i) //calculating probability
        {
            char lineChar  = tolower(line[i]);
            if(lineChar == 'a')
                rProbA++;
            else if(lineChar == 'c')
                rProbC++;
            else if(lineChar == 't')
                rProbT++;
            else if(lineChar == 'g')
                rProbG++;
        }
      }
      variance = variance / (numLines - 1); //variance calculated
      standardDeviation = sqrt(variance); //standard deviation calculated

      rProbA = rProbA / sum;
      rProbC = rProbC / sum;
      rProbT = rProbT / sum;
      rProbG = rProbG / sum;

      myFile << "Sum: " << sum << endl;
      myFile << "Number of Lines: " << numLines << endl;
      myFile << "Mean: " << mean << endl;
      myFile << "Variance: " << variance << endl;
      myFile << "Standard Deviation: " << standardDeviation << endl;
      myFile << "Relative Probability of Nulceotide A: " << rProbA << "\nRelative Probability of Nulceotide C: " << rProbC << "\nRelative Probability of Nulceotide T: " << rProbT << "\nRelative Probability of Nulceotide G: " << rProbG << endl;
      //myFile << "Total Probability(should be 1): " << rProbA + rProbC + rProbT + rProbG << endl; //TESTING

      myFile << "Relative Probability of Nulceotide Bigram AA: " << rProbA * rProbA << endl;
      myFile << "Relative Probability of Nulceotide Bigram AC: " << rProbA * rProbC << endl;
      myFile << "Relative Probability of Nulceotide Bigram AT: " << rProbA * rProbT << endl;
      myFile << "Relative Probability of Nulceotide Bigram AG: " << rProbA * rProbG << endl;

      myFile << "Relative Probability of Nulceotide Bigram CA: " << rProbC * rProbA << endl;
      myFile << "Relative Probability of Nulceotide Bigram CC: " << rProbC * rProbC << endl;
      myFile << "Relative Probability of Nulceotide Bigram CT: " << rProbC * rProbT << endl;
      myFile << "Relative Probability of Nulceotide Bigram CG: " << rProbC * rProbG << endl;

      myFile << "Relative Probability of Nulceotide Bigram TA: " << rProbT * rProbA << endl;
      myFile << "Relative Probability of Nulceotide Bigram TC: " << rProbT * rProbC << endl;
      myFile << "Relative Probability of Nulceotide Bigram TT: " << rProbT * rProbT << endl;
      myFile << "Relative Probability of Nulceotide Bigram TG: " << rProbT * rProbG << endl;

      myFile << "Relative Probability of Nulceotide Bigram GA: " << rProbG * rProbA << endl;
      myFile << "Relative Probability of Nulceotide Bigram GC: " << rProbG * rProbC << endl;
      myFile << "Relative Probability of Nulceotide Bigram GT: " << rProbG * rProbT << endl;
      myFile << "Relative Probability of Nulceotide Bigram GG: " << rProbG * rProbG << endl;

      srand(time(NULL)); //seeding the rand()
      for(int i = 0; i < 1000; ++i) //1000 string loop
      {
        c = sqrt(-2 * log(rand() / double(RAND_MAX))) * cos(2 * M_PI * (rand() / double(RAND_MAX)));
        distribution = (standardDeviation * c) + mean;
        string lineWrite = "";
        //myFile << distribution << endl; //TESTING
        for (int j = 0; j < round(distribution); ++j) //line length loop
        {
          double temp = rand() / double(RAND_MAX);
          if(temp >= 0 && temp < rProbA) //assign nucleotide values by concatenating to string
            lineWrite += 'a';
          else if (temp >= rProbA && temp < (rProbA + rProbC)) //these else if statemets don't actually need to check the lower bounds as it is already checked in previous if, but does so just in case
            lineWrite += 'c';
          else if (temp >= (rProbA + rProbC) && temp < (rProbA + rProbC + rProbT))
            lineWrite += 't';
          else if (temp >= (rProbA + rProbC + rProbT) && temp < (rProbA + rProbC + rProbT + rProbG))
            lineWrite += 'g';
        }
        //myFile << "String # " << i + 1 << ": "; //TESTING
        myFile << lineWrite << endl; //writes the finished nucleotide string
      }
    }
    else //if unable to open file, lets the user know
      cout << "Unable to open file" << endl;

  string cont = "", fileName = "";
  cout << "Would you like to process another list? (y/n):"<< endl; //check to process another list
  cin >> cont;
  if (cont != "y" && cont != "Y") //if no, breaks out of while loop
    break;

  cout << "What is the name of the next file?" << endl; //takes name of next file and while loop continues
  cin >> fileName;
  textFile.close();
  textFile.clear();
  textFile.open(fileName);
  }
  textFile.close(); //closes files and ends program
  myFile.close();
  return 0;
}





//location of text file for program testing; doesnt work, assumably because container can't access stuff outside of it
///Users/travismayer/Documents/CPSC_Courses/assign1/sampleDNA.txt
// actual location:
// sampleDNA.txt
