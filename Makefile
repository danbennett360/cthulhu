all:
	(cd game; make)

clean:
	(cd game; make clean);

commit:
	make clean
	git add -u
	git add -A
	git commit -m "update"
	git push -u origin master
