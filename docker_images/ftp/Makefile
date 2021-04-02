build:
	mount --bind ../target/src src/
	docker build -t kaguya_ftp .
	umount src/

run:
	docker run --rm -d -t --network lan kaguya_ftp
