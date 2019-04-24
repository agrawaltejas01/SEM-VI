





heart <- read.csv("Cleavland.csv", header = TRUE, sep = ",")
data <- heart
names(data) = c("age","sex","cp","trestbps","chol","fbs",
                "restecg","thalach","exang","oldpeak","slope","ca","thal","num")
#boxplot
boxplot(data$num~data$age, xlab = "age", ylab = "num")

#histogram
hist(data$num,  xlab = "types", main = "Types of Cancer")

#scatter_plot
plot(data$age, data$num, xlab = "age", ylab = "type", main = "Age dependency of cancer")

#satter plot using ggplot
ggplot(data = data, mapping = aes(x = age, y = num)) + geom_point()

#bar graphs
ggplot(data = data, mapping = aes(x = num)) + geom_bar()

#box plot with scatter plot added in it
#ggplot(data = data, mapping = aes(x = age, y = num), fill = factor(age)) + geom_boxplot()

#pie chart
labl = c("a", "b", "c", "d")
pie(data$num[1:4] , labels = labl, edges = 20, radius = 1)


#line plot
ggplot(data= data, mapping = aes(x = age, y = num)) + geom_line()
