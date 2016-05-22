#!/bin/sh
#$ -S /bin/sh

################################################################################
#                                                                              #
#  Title  : Make a job script files and throw a that files                     #
#  Program Name : rootjob.sh                                                   #
#                                                                              #
#  Detail : Create                                                             #
#  Date   : 2016.05.20                                                         #
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

					# Set work directory
WORK_DIR=/home/a-kashiwagi/src/bioinformatics/minibatch/result04x50e

					# Set learning data file
LEARNING_DATA=/home/a-kashiwagi/work/for_ExtractORF/NC_000908_learn.bit

					# Set teaching data file
TEACHING_DATA=/home/a-kashiwagi/work/for_ExtractORF/NC_000908_teach.bit

					# Set initialize data file
INIT_DATA=${WORK_DIR}/init_minibatch.dat

					# Set result data file
RESULT_DATA=${WORK_DIR}/result_minibatch

					# Set summary data file
SUMMARY_DATA=${WORK_DIR}/sum_minibatch.dat

					# Set learning times
LEARNING_TIMES=4
					# Set unit number
UNIT_NUM=400
					# Set row number of learning data
LEARNING_DATA_ROW=11057
					# Set row number of teaching data
TEACHING_DATA_ROW=11057
					# Set number of split
SPLIT=50
					# Set DNN program file name
PRG=/home/a-kashiwagi/src/bioinformatics/minibatch/dna_recognizer_bin

					# Set summary program file
SUM=/home/a-kashiwagi/src/bioinformatics/minibatch/sum_delta_bin

					# Set job file name
SH_FILE=job
					# Make inital file
echo -n "Making initial data file..."
$PRG $LEARNING_TIMES $UNIT_NUM $LEARNING_DATA $LEARNING_DATA_ROW $TEACHING_DATA $TEACHING_DATA_ROW -1
echo "done."
					# Excecute jobs
for cnt in `seq -w 0 $((${SPLIT}-1))`
do
	echo "#!/bin/sh"		 > ${SH_FILE}${cnt}.sh
	echo "#$ -S /bin/sh"		>> ${SH_FILE}${cnt}.sh
	echo "cd $WORK_DIR"		>> ${SH_FILE}${cnt}.sh
	echo "pwd"			>> ${SH_FILE}${cnt}.sh
	echo "hostname"			>> ${SH_FILE}${cnt}.sh
	echo "date"			>> ${SH_FILE}${cnt}.sh
	echo "$PRG $LEARNING_TIMES $UNIT_NUM $LEARNING_DATA $LEARNING_DATA_ROW $TEACHING_DATA $TEACHING_DATA_ROW $cnt" >> ${SH_FILE}${cnt}.sh
	echo "date"			>> ${SH_FILE}${cnt}.sh
	echo "echo to stderr 1>&2"	>> ${SH_FILE}${cnt}.sh

	qsub ${SH_FILE}${cnt}.sh
	sleep 20
done
					# Make a completion shell

echo "#!/bin/sh"			 > completion.sh
echo "#$ -S /bin/sh"			>> completion.sh
echo "cd $WORK_DIR"			>> completion.sh
echo "pwd"				>> completion.sh
echo "hostname"				>> completion.sh
echo "date"				>> completion.sh
echo "$PRG 20 $UNIT_NUM $LEARNING_DATA $LEARNING_DATA_ROW $TEACHING_DATA $TEACHING_DATA_ROW $SPLIT" >> completion.sh
echo cp ${RESULT_DATA}`seq -f '%03g' ${SPLIT} ${SPLIT}`.dat $INIT_DATA >> completion.sh
echo date				>> completion.sh
echo "echo to stderr 1>&2"		>> completion.sh

					# Make a summary shell

echo "#!/bin/sh"			 > summary.sh
echo "#$ -S /bin/sh"			>> summary.sh
echo "cd $WORK_DIR"			>> summary.sh
echo "pwd"				>> summary.sh
echo "hostname"				>> summary.sh
echo "date"				>> summary.sh
echo "$SUM 20 $UNIT_NUM $INIT_DATA $LEARNING_DATA_ROW $RESULT_DATA $TEACHING_DATA_ROW $SPLIT" >> summary.sh
echo "mv $INIT_DATA ${INIT_DATA}.bak"	>> summary.sh
echo "cp $SUMMARY_DATA $INIT_DATA"	>> summary.sh
echo "date"				>> summary.sh
echo "echo to stderr 1>&2"		>> summary.sh

#/home/a-kashiwagi/src/bioinformatics/minibatch/dna_recognizer 4 400 /home/a-kashiwagi/work/for_ExtractORF/NC_000908_learn.bit 11057 /home/a-kashiwagi/work/for_ExtractORF/NC_000908_teach.bit 11057 0
