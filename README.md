# Libasm

## Overview
Make simple asm functions. (in docker)

### Todo
- [ ] ft_strlen (man 3 strlen)
size_t strlen(const char *s);
- [ ] ft_strcpy (man 3 strcpy)
size_t strlcpy(char * restrict dst, const char * restrict src, size_t dstsize);
- [ ] ft_strcmp (man 3 strcmp)
int strcmp(const char *s1, const char *s2);
- [ ] ft_write (man 2 write)
ssize_t write(int fildes, const void *buf, size_t nbyte);
- [ ] ft_read (man 2 read)
ssize_t read(int fildes, void *buf, size_t nbyte);
- [ ] ft_strdup (man 3 strdup, you can call to malloc)
char * strdup(const char *s1);


### How to run it on Linux

### How to run it on M1
**Install the tools : colima & docker buildx**

Install colima (use docker-machines)
```shell
brew install colima
colima start -a x86_64
```

Install buildx:
```shell
brew install docker-buildx
mkdir -p ~/.docker/cli-plugins
ln -sfn $(which docker-buildx) ~/.docker/cli-plugins/docker-buildx
docker buildx install
```

Build and run the container:
```shell
# Built with:
$> export DOCKER_DEFAULT_PLATFORM=linux/amd64; docker build -t nihuynh/nasm-gcc .
# Run as interactive :
$> docker run --platform linux/amd64 -it -v $(pwd):/workdir nihuynh/nasm-gcc
```

### Ressources
http://www.software-architects.com/devblog/2019/04/tiny-docker-image
https://cs.lmu.edu/~ray/notes/nasmtutorial/
https://www.nasm.us/doc/

grafana
https://loganmarchione.com/2020/05/always-on-grafana-dashboard-using-raspberry-pi-touchscreen/