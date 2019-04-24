







library("SnowballC")
library("tm")
library("wordcloud")
library("RColorBrewer")

#Read file
filepath <- "/home/deception/Practice/Text_Mining_7/aboutPICT .txt"
text <- readLines(filepath)

#Create Corpus Object
docs <- Corpus(VectorSource(text))
inspect(docs)

#Data cleaning
toSpace <- content_transformer(function(x, pattern) gsub(pattern, " ", x))

docs <- tm_map(docs, toSpace, "@")
docs <- tm_map(docs, toSpace, "/")
docs <- tm_map(docs, toSpace, "\\|")

#Data Transformation
#Tolower
docs <- tm_map(docs, content_transformer(tolower))

#Remove Numbers
docs <- tm_map(dos, removeNumbers)

#Remove Stopwords
docs <- tm_map(docs, removeWords, stopwords("english"))

#Remove Punctuation
docs <- tm_map(docs, removePunctuation)

#Remove Whitespace
docs <- tm_map(docs, stripWhitespace)

#Term-document matrix
dtm <- TermDocumentMatrix(docs)
m <- as.matrix(dtm)
v <- sort(rowSums(m), decreasing = TRUE)
d <- data.frame(words = names(v), freq = v)

#Wordcloud generation
wordcloud(words = d$words, freq = d$freq, min.freq = 1,
          max.words = 200, random.order = FALSE,rot.per = 20,
          colors = brewer.pal(8,"Blues"))