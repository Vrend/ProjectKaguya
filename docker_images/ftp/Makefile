build:
	mkdir src/
	mount --bind ../target/src src/
	docker build -t kaguya_ftp .
	umount src/

run:
	docker run --rm -d -t --name kaguya_ftp --network lan kaguya_ftp
