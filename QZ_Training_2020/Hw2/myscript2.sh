N=0
IFS=$'\n'
for line in $(ls -alFh .)
do
# if [ -e  ]; then echo "a"; fi  will echo a
#    if [ -d $(echo ${line} | awk '{print $9}') ]
    if [ "${line:0:1}" = "d" ]
    then
        echo "${line}"
        N=`expr $N + 1`
    fi
done
echo "$(pwd)共有上述${N}个目录，$(pwd)总大小为$(du -sh | awk '{print $1}')"
