







facebook <- read.csv("dataset_Facebook.csv", header = TRUE, sep = ";")
data <- facebook
print (data[1:10, 1:5])
#-------------------------------------------------------------------------------
sub <- subset(data, Category == 3 & Type == "Status")
print(sub)
#--------------------------------------------------------------------------------
new_sub <- subset(data, Category==2 & Type=="Status")
print(new_sub)
total_status = merge(sub, new_sub, by="Type")

vector_data <- data[c("Category")]
sorted_data <- data[order(data$Category),]
 #-------------------------------------------------------------------------------

Trans <- t(data[1:10, 1:5])
#-------------------------------------------------------------------------------

library(reshape2)
library(reshape)
to_be_molten <- head(data[, 1:3], 10)
print(to_be_molten)

molten <- melt(to_be_molten, id = c("Type", "Category"))
#--------------------------------------------------------------------------------

casted <- dcast(molten, formula = Type ~ Category+variable, sum)
