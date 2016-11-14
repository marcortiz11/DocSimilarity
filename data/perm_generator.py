from random import shuffle

outdir = "permutations"
wordfile = "words.txt"

f = open(wordfile, 'r')
words = f.read().splitlines()
f.close()

for i in range(20):
    filename = str(i+1) + ".txt"
    f = open(outdir + "/" + filename, 'w')
    shuffle(words)
    text = ' '.join(words)
    f.write(text)
    f.close()
