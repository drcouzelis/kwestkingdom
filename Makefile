all:
	 make -C src

backup:
	 cp -rf . /tmp/kwestkingdom
	 cd /tmp/kwestkingdom && make clean
	 cd /tmp && tar -zcf kwestkingdom-`date "+%Y.%m.%d.%H.%M.%S"`.tar.gz kwestkingdom
	 cd /tmp && rm -rf kwestkingdom
	 mv /tmp/kwestkingdom*.gz ../backup

clean:
	 make -C src clean

win:
	 cp -f res/resources.dat Windows/resources.dat
	 make -C src win

