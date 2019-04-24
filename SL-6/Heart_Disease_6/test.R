






data <- read.csv("BreastCancerWc.csv", header = TRUE, sep = ",")
print(data[1:10, 1:5])

boxplot(data$X5,horizontal = 1)
#ifelse(data$X5>=2 | data$X5<=5, print("Outlier"), data$X5 )
data$X5 = ifelse(data$X5<=2 | data$X5>=5, 4, data$X5 )

#range
brk = c(1,3,5,7,9)
data$X1.5 = cut(data$X1.5, breaks = brk, include.lowest = TRUE)

#Replacing
gsub(2,"None", data$X2.1)

layout
