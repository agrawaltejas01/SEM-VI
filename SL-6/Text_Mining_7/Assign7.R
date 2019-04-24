







# Step 1: Install
#install.packages("tm")           # for text mining
#install.packages("SnowballC")    # for text stemming
#install.packages("wordcloud")    # word-cloud generator 
#install.packages("RColorBrewer") # color palettes

# Step 2: Load
library("tm")
library("SnowballC")
library("wordcloud")
library("RColorBrewer")

# Step 3: Text mining

#load the text

# Read the text file 
filePath <- "/home/deception/Practice/Text_Mining_7/aboutPICT .txt"
text <- readLines(filePath)

# Load the data as a corpus
docs <- Corpus(VectorSource(text))
inspect(docs)

#Text transformation
#Transformation is performed using tm_map() function to replace, for example, special characters from the text.
#Replacing "/","@","|" with space:

#Text transformation

toSpace <- content_transformer(function (x , pattern ) gsub(pattern, " ", x))
docs <- tm_map(docs, toSpace, "/")
docs <- tm_map(docs, toSpace, "@")
docs <- tm_map(docs, toSpace, "\\|")

#Cleaning the text

# Convert the text to lower case
docs <- tm_map(docs, content_transformer(tolower))

# Remove numbers
docs <- tm_map(docs, removeNumbers)

# Remove english common stopwords
docs <- tm_map(docs, removeWords, stopwords("english"))

# Remove your own stop word
# specify your stopwords as a character vector
docs <- tm_map(docs, removeWords, c("blabla1", "blabla2")) 

# Remove punctuations
docs <- tm_map(docs, removePunctuation)

# Eliminate extra white spaces
docs <- tm_map(docs, stripWhitespace)

# Text stemming
# docs <- tm_map(docs, stemDocument)

#Step 4 : Build a term-document matrix

dtm <- TermDocumentMatrix(docs)
m <- as.matrix(dtm)
v <- sort(rowSums(m),decreasing=TRUE)
d <- data.frame(word = names(v),freq=v)
head(d, 10)


#Step 5 : Generate the Word cloud
set.seed(1234)
wordcloud(words = d$word, freq = d$freq, min.freq = 1,
          max.words=200, random.order=FALSE, rot.per=0.35, 
          colors=brewer.pal(8,Blues))


