







#include packages
library("tm")
library("wordcloud")
library("SnowballC")
library("RColorBrewer")

#read file
filepath <- "/home/deception/Practice/Text_Mining_7/aboutPICT .txt"
text <- readLines(filepath)
#print(text)

#pass to Corpus
docs <- Corpus(VectorSource(text))
inspect(docs)

#-----------------Data Cleaning---------------------
#Remove outliers
toSpace <- content_transformer(function(x, pattern) gsub(pattern, " ", x))

docs <- tm_map(docs, toSpace, "@")
docs <- tm_map(docs, toSpace, "/")
docs <- tm_map(docs, toSpace, "\\|")

#-----------------Data Transformation---------------

#Convert to lowercase
docs <- tm_map(docs, content_transformer(tolower))

#Remove Numbers
docs <- tm_map(docs, removeNumbers)

#Remove Stopwords
docs <- tm_map(docs, removeWords, stopwords("english"))

#Remove Punctuation
docs <- tm_map(docs, removePunctuation)

#Strip Whitespaces
docs <- tm_map(docs, stripWhitespace)

#Create a term-Document Matrix
dtm <- TermDocumentMatrix(docs)
m <- as.matrix(dtm)
v <- sort(rowSums(m), decreasing = TRUE)
d <- data.frame(words = names(v), freq = v)
head(d,10)

#Create Wordcloud
set.seed(1234)
wordcloud(words = d$words, freq = d$freq, min.freq = 1,
          max.words = 200, random.order = FALSE, rot.per = 20,
          colors = brewer.pal(8,"BuGn"))

#Create Word cloud
