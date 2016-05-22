#!/bin/sh
#$ -S /bin/sh

################################################################################
#                                                                              #
#  Title  : Script of make a splitted csv files and that graph files           #
#  Program Name : get_allcsv.sh                                                #
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
# -------+---------+---------+---------+---------+---------+---------+---------#
#234567890123456789012345678901234567890123456789012345678901234567890123456789#
################################################################################

					# Set Rscript command name
RCOM=~/bin/Rscript
					# Set script file name for R
SCRIPT=get_graph.R
					# Set log file name
LOG_FILE="../detect_ma100b.log"
					# Moving Average Interval
MAI=100
					# Set output interval [lines]
INTERVAL=10000
					# Set end count
END_COUNT=580000
					# File number
FILE_NUMBER=0
					# Set start count
COUNTER=$((${INTERVAL}-${MAI}/2+1))

					# Output loop
for cnt in `seq -w $COUNTER $INTERVAL $END_COUNT`
do
	echo "Processing: No.${cnt} to: ${FILE_NUMBER}.csv"

	if [ ${FILE_NUMBER} -eq 0 ]
	then
					# Case of first time
		cat ${LOG_FILE} | head -${cnt} > ${FILE_NUMBER}.csv
	else
					# Case of over second times
		cat ${LOG_FILE} | head -${cnt} | tail -${INTERVAL} > ${FILE_NUMBER}.csv
	fi
					# Make graphs by using R
	${RCOM} ${SCRIPT} ${FILE_NUMBER} ${INTERVAL}

					# Increase counter
	FILE_NUMBER=$((${FILE_NUMBER}+1))
done
