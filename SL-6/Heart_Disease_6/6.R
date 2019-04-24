





#read dataset 
heart = read.csv("Cleavland.csv", header = TRUE, sep = ",")

names(heart) <- c("age","sex","cp","trestbps","chol","fbs","restecg","thalach","exang","oldpeak","slope","ca","thal","num")
#print(data)

data <- heart

# Error Correction and data cleaning
#mean(data$num, na.rm = TRUE)
#summary(data$num)

#data$ca = ifelse(is.na(data$ca), median(data$ca, na.rm = TRUE), data$ca)
#summary(data$cal)
print("----------------------------------------------")
data$thal = ifelse(is.na(data$thal), median(data$thal, na.rm = TRUE), data$thal)
#summary(data$thal)

#-----------------------------------Transformation-------------

brk = c(50,100,150,200,250,300,350)

data$trestbps = cut(data$trestbps, brk, include.lowest = TRUE)

data$sex = gsub("0", "Male", data$sex)
data$sex = gsub("1", "Female", data$sex)

#-----------------------------------Integration-------------

test1 <- c("a", "b", "c")
test <- c("d", "e", "f")

RBIND <- rbind(test, test1)
#print(RBIND)

CBIND <- cbind(test, test1)
#print(CBIND)

#------------------------Missing values--------------------
#data$ca = c("?")
#print(head(data$ca))

data$ca = ifelse(data$ca=='?', NA, data$ca)
#print(head(data$ca))

data$ca = ifelse(is.na(data$ca), median(data$ca, na.rm = TRUE), data$ca)
#print((data$ca))

#------------------------------Splitting Datasets--------------
#print(dim(data))
#train_set = data[1:200, ]
#test_set = data[200:302, ]

library(caTools)

split = sample.split(data$age, SplitRatio = 2/3)
train_set = subset(data, split = TRUE)
test_set = subset(data, split = FALSE)

#------------Regression---------------
#install.packages("caTools")


regressor = lm(formula = train_set$num ~ train_set$age+train_set$ca, data = train_set)

age_predict = predict(regressor, newdata = test_set)

age_predict = round(age_predict)
#print(age_predict)

library(e1071)
#ibrary(caret)
#confusionMatrix(factor(age_predict, levels = 0:1),factor(test_set$num, levels = 0:1))

#---------------- Multiple Regression----------------


mul_regressor = lm(formula = train_set$num ~ train_set$age+train_set$cp+train_set$trestbps+train_set$chol)

age_predict = predict(mul_regressor, newdata = test_set)
age_predict = round(age_predict)

#print(age_predict)

library(e1071)
#library(caret)
#confusionMatrix(factor(age_predict , levels = 0:1), factor(test_set$num , levels = 0:1))

#--------------------------KNN----------------------

library(class)

new_train_set = data[200:302,]
new_test_set = data[1:200,]

train_set_label = data[1:200, 14]
test_set_label = data[200:302, 14]

classifier = knn(train = new_train_set, test = new_test_set, cl = train_set_label, k=10)

library(gmodels)
CrossTable(x=test_set_labels,y=classifier,prop.chisq = FALSE)


