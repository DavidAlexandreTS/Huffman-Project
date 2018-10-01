library(ggplot2)

result <- read.table("C:\\Users\\david\\Desktop\\Project of Data Structs\\3. Counting and Plotting\\Graficos.txt",header=F)
result = unlist(result)

i = j = 1
x = y1 = y2 = rep(0, length(result)/3)

while(i<=length(result)){
  x[j] = result[i]
  y1[j] = result[i+1]
  y2[j] = result[i+2]
  i = i + 3
  j = j + 1
}

dat1 <- data.frame(
  Number = x,
  Tree = y1,
  AVL = y2
)

p <- qplot(ylab = "Number of comparations", xlab = "Elements") +
  ggtitle("Binary Tree vs AVL") + 
  theme(plot.title = element_text(size=18, face="bold",hjust=0.5)) +
  geom_line(data = dat1, aes(x = Number, y = Tree), size = 1, color = '#ce0606') + 
  geom_point(data = dat1, aes(x = Number, y = Tree), size = 2, color = '#ce0606') + 
  geom_line(data = dat1, aes(x = Number, y = AVL), size = 1, color = '#003366') + 
  geom_point(data = dat1, aes(x = Number, y = AVL), size = 2, color = '#003366')

print(p)