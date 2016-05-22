################################################################################
#                                                                              #
#  Title  : Script of make a moving average and a detect graph                 #
#  Program Name : get_graph                                                    #
#                                                                              #
#  Detail : Create                                                             #
#  Date   : 2016.05.12                                                         #
#  Author : Akihiro Kashiwagi                                                  #
#  e-mail : a-kashiwagi@mippi-mail.com                                         #
#                                                                              #
#  Replace --------------------------------------------------------------------#
#                                                                              #
#  Date   :                                                                    #
#  Author :                                                                    #
#  Deteil :                                                                    #
#                                                                              #
#--------+---------+---------+---------+---------+---------+---------+---------#
#234567890123456789012345678901234567890123456789012345678901234567890123456789#
################################################################################

					# Get argvs
argv=commandArgs(T)
in_filename=as.numeric(argv[1])
interval=as.numeric(argv[2])
					# Load library
library(ggplot2)
					# Load csv file
cat(paste('Load ',in_filename,'.csv','\n',sep=""))
detect = read.csv(paste(in_filename,'.csv',sep=""), header=F)

					# Set start and end number
start=detect$V1[1]
end=detect$V1[length(detect$V1)]
					# Set a saving picture file name
cat(paste('Save ',in_filename,'_',start,'-',end,'.jpg','\n',sep=""))
jpeg(paste(in_filename,"_",start,"-",end,'.jpg',sep=""),width=1280,height=480)

					# Put a moving average graph
					#                        by using qplot
qplot(detect$V1,detect$V2,geom="line",xlab="bp",ylab="detect",ylim=c(0,1))

					# Close a save file
dev.off()
					# Make FFT data
y <- fft(detect$V2)
y_edit = y[1:50]
y_edit[1] = 0
					# Set a saving picture file name
cat(paste('Save ',in_filename,'_',start,'-',end,'_fft.jpg','\n',sep=""))
jpeg(paste(in_filename,"_",start,"-",end,'_fft.jpg',sep=""),width=1280,height=480)

					# Put a fft graph by using qplot
x = c(0:(length(y_edit)-1))
qplot(x,abs(y_edit),geom="bar",stat="identity",xlab="freq",ylab="power")

					# Close a save file
dev.off()

					# Set cut off frequency
y_edit = y
for(i in 10:length(y_edit)){
    y_edit[i] = 0
}
					# Cut off DC
y_edit[1] = 0
					# Make Inverse FFT data
yinverse <- fft(y_edit,inverse=T)

					# Set a saving picture file name
cat(paste('Save ',in_filename,'_',start,'-',end,'_ifft10.jpg','\n',sep=""))
jpeg(paste(in_filename,"_",start,"-",end,'_ifft10.jpg',sep=""),width=1280,height=480)

					# Put a detect graph by using qplot
x = c(detect$V1[1]:detect$V1[length(yinverse)])
#qplot(x,abs(yinverse),geom="line",ylim=c(0,3500),xlab="bp",ylab="detect")
qplot(x,abs(yinverse),geom="line",xlab="bp",ylab="detect")

					# Close a save file
dev.off()
cat('done.\n')
