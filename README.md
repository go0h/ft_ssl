# ft_ssl

### Implementation cryptographic hash functions

<a href="https://en.wikipedia.org/wiki/MD5">MD5</a>
<a href="https://en.wikipedia.org/wiki/SHA-2">SHA2</a>

### Get started
```
git clone https://github.com/go0h/ft_ssl.git && cd ft_ssl && make
```

### Usage
```
Usage: ./ft_ssl hash_func [options]
Options:
        -h - for print this help
        -p - echo STDIN to STDOUT and append the checksum to STDOUT
        -q - quiet mode
        -r - reverse the format of the output
        -s STRING - print the sum of the given string
Message Digest commands:
MD5            SHA256         SHA224         SHA512
SHA384         SHA512-256     SHA512-224
```
