







data <- read.csv("dataset_Facebook.csv", header = TRUE, sep = ";")
#print(data)

print(dim(data))
print(ncol(data))
print(nrow(data))

#-------------------------
sub_data <- subset(data, Type == "Photo")
#print(sub_data[1:10, 1:3])

new_sub <- subset(data, Category == 2)
#print(new_sub[1:10, 1:5])

#-----------
merged <- merge(sub_data, new_sub, by="Type")
#print(merged[1:10, 1:4])

#-----------------------
vector_data = data[c("Type", "Category")]
#print(vector_data)

sorted_data <- vector_data[order(vector_data$Category),]
#print(sorted_data[1:10,])

#---------------------

transpose = t(sorted_data[1:10,])
print(transpose)

#---------------

library(reshape)
library(reshape2)
to_be_molten = head(data[,1:3], 10)
#print(to_be_molten)

molten = melt(to_be_molten, id = c("Type"))
#print(molten)

#-----------

casted = dcast(molten, formula = Type ~ variable, sum)
print(casted)