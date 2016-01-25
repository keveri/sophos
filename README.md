[![BSD3 License](https://img.shields.io/badge/license-BSD3-blue.svg?style=flat-square)](https://tldrlegal.com/license/bsd-3-clause-license-%28revised%29)

# σοφός (sophos)
_Socket server sharing wisdom._

Reads rows from a given file as wisdoms. Responds with randomly chosen wisdom when a client connects.

## Setup
Build:
```
$ make
```

Clean:
```
$ make clean
```

## Usage
Man page:
```
$ man ./sophos.1
```

Examples:
```
$ bin/sophos -p 4444 wisdoms.txt

$ cat wisdoms.txt | sophos -p 4444
```
