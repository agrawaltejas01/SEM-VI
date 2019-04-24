







library("tm")
library("SnowballC")
library("wordcloud")
library("RColorBrewer")

#Read the file
filepath <- "/home/deception/Practice/Text_Mining_7/aboutPICT .txt"
text <- readLines(filepath)
#print(text)

#Send the file to Corpus
docs <- Corpus(VectorSource(text))
inspect(docs)


#------------------------Data Transformation-------------------

#Remove all the outliers(not considered by english language)

toSpace <- content_transformer(function (x, pattern) gsub(pattern, " ", x))
docs <- tm_map(docs, toSpace, "@")
docs <- tm_map(docs, toSpace, "/")
docs <- tm_map(docs, toSpace, "\\|")

#print(docs)

#------------------------Data Cleaning------------------------

#Convert to lower case
docs <- tm_map(docs, content_transformer(tolower))

#Remove numbers
docs <- tm_map(docs, removeNumbers)

#Remove stopwords
docs <- tm_map(docs, removeWords, stopwords("english"))

#Remove Punctuations
docs <- tm_map(docs, removePunctuation)

#Remove whitespace
docs <- tm_map(docs, stripWhitespace)

#--------------Build a term-document Matrix------------------
dtm <- TermDocumentMatrix(docs)
m <- as.matrix(dtm)
v <- sort(rowSums(m), decreasing = TRUE)
d <- data.frame(word = names(v), freq = v )
head(d,10)

#-------------Generate a word cloud---------------------------
set.seed(1234)
wordcloud(words = d$word, freq = d$freq, max.words = 200
          , random.order = FALSE, rot.per = 20
          ,min.freq = 1, colors = brewer.pal(8, name = "Blues"))
