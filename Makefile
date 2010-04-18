all:
	 rm -rf Linux/share/kwestkingdom/img
	 rm -rf Linux/share/kwestkingdom/snd
	 rm -rf Linux/share/kwestkingdom/bgm
	 cp -r res/img Linux/share/kwestkingdom/
	 cp -r res/snd Linux/share/kwestkingdom/
	 cp -r res/bgm Linux/share/kwestkingdom/
	 make -C src

backup:
	 cp -rf . /tmp/kwestkingdom
	 cd /tmp/kwestkingdom && make clean
	 cd /tmp && tar -zcf kwestkingdom-`date "+%Y.%m.%d.%H.%M.%S"`.tar.gz kwestkingdom
	 cd /tmp && rm -rf kwestkingdom
	 mv /tmp/kwestkingdom*.gz ../backup

clean:
	 rm -rf Linux/share/kwestkingdom/img
	 rm -rf Linux/share/kwestkingdom/snd
	 rm -rf Linux/share/kwestkingdom/bgm
	 make -C src clean

win:
	 cp -f res/resources.dat Windows/resources.dat
	 make -C src win

