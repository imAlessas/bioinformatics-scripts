# Pattern matching application example (CSI)

You have been assigned by the Department of Scientific Investigations to analyze the DNA discovered in 3 unsolved cases and compare it with that of 3 suspects to reveal the culprit.

## Scientific background

DNA, the carrier of genetic information in living organisms, has been used in scientific investigations for decades. But how exactly does DNA profiling work? Given a DNA sample, how do forensic investigators manage to identify to whom it belongs?

DNA is actually composed of a sequence of molecules, called _nucleotides_, that form a double helix. Each DNA nucleotide contains one of four bases: adenine (__A__), cytosine (__C__), guanine (__G__), or thymine (__T__). Every human cell contains billions of these nucleotides arranged in sequence. Some portions of this sequence, known as the _genome_, are the same or very similar in all humans. However, other parts of the sequence have higher genetic diversity and therefore vary among individuals of the same species.

One of the places where DNA tends to have high genetic diversity is in Short Tandem Repeats (__STRs__). An STR is a short DNA sequence that tends to repeat multiple times consecutively. The number of times a particular STR repeats varies greatly among different individuals.

The probability that two different individuals have the same number of repetitions for the same STR is very low. By using multiple STRs instead of just one, we can improve the accuracy of DNA profiling, further reducing this probability. For instance, FBI databases utilize 20 different STRs, with a probability that two DNA profiles match "by chance" equal to or less than one in $10^{26}$.

Simplifying things a bit, we can imagine these databases as files where each line corresponds to an individual, listing their name followed by the number of detected STRs for each considered STR described in the first line.

| Name    | AGAT | AATG | TATC |
|---------|------|------|------|
| Alice   | 28   | 42   | 14   |
| Bob     | 17   | 22   | 19   |
| Charlie | 36   | 18   | 25   |

In the example above, Alice has the _AGAT_ sequence repeated 28 times consecutively somewhere in her DNA, the _AATG_ sequence repeated 42 times, and _TATC_ repeated 14 times.

Therefore, given a DNA sequence, which is essentially a string for us, we can identify to whom it belongs using bioinformatics techniques. This involves developing an algorithm that analyzes the sequence and information in the "database". Specifically, it will:

- Analyze the character sequence representing the DNA found at the crime scene by searching for the number of consecutive occurrences of each STR present in the investigative database.

- Compare the values found (= profile) with those corresponding to the "profiled" individuals, and if there is a match, there is a good probability that individual is the culprit.

In reality, the analysis is a bit more complex than described here, but let's settle for this simplified explanation.

## Specifications

Write an executable program that identifies to whom the DNA sequence belongs (the guidelines are for a C++ program, but you can easily adapt them).

1. The program will require two command-line arguments: the name of the file containing the profiles of the suspects and the name of the file containing the DNA sequence to be identified.

2. The first line of the profiles file will contain the word "name" followed by the sequences of the considered STRs. The subsequent lines will contain the name of the individual followed by the counts of the detected STRs in their DNA.

3. For each STR sequence, the program should calculate the longest run of consecutive repetitions of that STR in the DNA to be identified.

4. If the STR counts match with any known profiles, the name of the suspected culprit should be output; otherwise, it should print "no match found". You can assume that an STR count will match with at most one individual.

### Files

- [Suspects](./dataset/suspects.txt)

- [DNA trace 1](./dataset/DNA-trace-1.txt)

- [DNA trace 2](./dataset/DNA-trace-2.txt)

- [DNA trace 3](./dataset/DNA-trace-3.txt)

- [DNA trace 4](./dataset/DNA-trace-4.txt)

### Usage

    g++ main.cpp -o main
    
    ./main suspects.txt DNA-trace-1.txt
