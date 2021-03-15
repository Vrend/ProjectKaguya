current_dir = $(shell pwd)

build:
	docker build -t kaguya_flag .

run:
	docker run -it --network wan -v ${current_dir}/SHARED:/wrkdr/SHARED kaguya_flag
