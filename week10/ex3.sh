rm _ex3.txt
echo TeaWide > _ex3.txt
chmod a-x _ex3.txt
ls -lah | grep _ex3.txt > ex3.txt
chmod uo+rwx _ex3.txt
ls -lah | grep _ex3.txt >> ex3.txt
chmod g+rwx _ex3.txt
ls -lah | grep _ex3.txt >> ex3.txt
echo "1) rw- rw- --- (read and write for user and group)
2) rwx rwx r-x (all for user and group, read and execute for other)
3) rwx rwx rwx (all for all)" >> ex3.txt
