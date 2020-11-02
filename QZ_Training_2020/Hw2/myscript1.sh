echo -e "当前时间：\c"
echo `date`

echo -e "pwd:  $(pwd)"

echo -e "users:  $(users)  SHELL: $SHELL"

WORKDIR=$(pwd)

echo -e "\$WORKDIR =$WORKDIR"
echo -e "$WORKDIR 总大小: $(du -sh $WORKDIR | awk '{print $1}')"

sleep 5s

echo -e "当前时间：\c"
echo `date`
