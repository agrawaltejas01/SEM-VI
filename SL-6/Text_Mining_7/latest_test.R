







library("tm")
library("SnowballC")
library("RColorBrewer")
library("wordcloud")

#Read file
filepath <- "/home/deception/Practice/Text_Mining_7/aboutPICT .txt"
text <- readLines(filepath)

#Create Corpus object
docs <- Corpus(VectorSource(text))
inspect(docs)

#Remove Outliers
toSpace <- content_transformer(function(x,pattern) gsub(pattern = pattern, " ", x))

docs <- tm_map(docs, toSpace, "@")
docs <- tm_map(docs, toSpace, "\\|")
docs <- tm_map(docs, toSpace, "/")

#convert to lower case
docs <- tm_map(docs, content_transformer(tolower))

#Remove numbers
docs <- tm_map(docs, removeNumbers)

#Remove Punctuations
docs <- tm_map(docs, removePunctuation)

#Remove Stopwords
docs <- tm_map(docs, removeWords, stopwords("english"))

#Remove Whitespace
docs <- tm_map(docs, stripWhitespace)

#Convert to Term-document matrx
dtm <- TermDocumentMatrix(docs)
m <- as.matrix(dtm)
v <- sort(rowSums(m), decreasing = TRUE)
d <- data.frame(word = names(v), freq = v)
head(d,10)

# Generate wordcloud 
set.seed(1234)
wordcloud(words = d$word, freq = d$freq, max.words = 200
          , random.order = FALSE, rot.per = 20
          ,min.freq = 1, colors = brewer.pal(8, name = "Blues"))
