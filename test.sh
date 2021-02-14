#!/bin/bash

GREEN="\e[32m"
RED="\e[31m"
EOC="\e[0m"

hashes=(md5 sha256 sha224 sha512 sha384 sha512-256 sha512-224)

for item in ${hashes[*]}
do
	diff <(echo "pickle rick" | openssl ${item}) <(echo "pickle rick" | ./ft_ssl ${item}) > res

	diff <(echo "" | openssl ${item}) <(echo "" | ./ft_ssl ${item}) >> res

	diff <(openssl ${item} Makefile) <(./ft_ssl ${item} Makefile) >> res
	diff <(openssl ${item} author) <(./ft_ssl ${item} author) >> res
	diff <(openssl ${item} ft_ssl) <(./ft_ssl ${item} ft_ssl) >> res

	diff <(echo "pickle rick" | openssl ${item} -r) \
		<(echo "pickle rick" | ./ft_ssl ${item} -r)  >> res

	diff <(openssl ${item} -r Makefile) <(./ft_ssl ${item} -r Makefile) >> res
	diff <(openssl ${item} -r author) <(./ft_ssl ${item} -r author) >> res
	diff <(openssl ${item} -r ft_ssl) <(./ft_ssl ${item} -r ft_ssl) >> res

	echo 'is ${item}("salt") a salted hash? :thonking_face:' > tmp
	diff <(openssl ${item} tmp) <(./ft_ssl ${item} tmp) >> res

	diff <(echo "Magic mirror on the wall, think I wanna smash them all?" | openssl ${item}) \
		<(echo "Magic mirror on the wall, think I wanna smash them all?" | ./ft_ssl ${item}) >> res

	diff <(echo "Speed up now, Gas Pedal??" | openssl ${item}) \
		<(echo "Speed up now, Gas Pedal??" | ./ft_ssl ${item}) >> res

	echo "Lorem ipsum dolor amet thundercats letterpress cray
		portland cornhole coloring book twee prism hexagon mixtape pork
		belly hell of four dollar toast disrupt. Hammock PBR&B bicycle
		rights selvage street art, lumbersexual gochujang vegan hot
		chicken. Meggings drinking vinegar biodiesel poke roof party
		tote bag cloud bread ethical. Glossier flannel 8-bit hexagon
		selvage adaptogen farm-to-table offal knausgaard pickled." > tmp

	diff <(openssl ${item} tmp) <(./ft_ssl ${item} tmp) >> res
	rm -rf tmp

	diff <(echo "privet kak dela?" | ./ft_ssl ${item} Makefile)\
		<(openssl ${item} Makefile) >> res

	diff <(./ft_ssl ${item} inc/*) <(openssl ${item} inc/*) >> res

	diff <(./ft_ssl ${item} src/hash/*) <(openssl ${item} src/hash/*) >> res

	if [ -z "$(cat res)" ] ;
		then printf "${GREEN}${item} - OK${EOC}\t${COR}\n"
		else printf "${RED}${item} - KO${EOC}\t${COR}\n$(cat res)\n"
	fi
	rm -rf res
done
