#!/bin/bash

diff <(echo "pickle rick" | openssl md5) <(echo "pickle rick" | ./ft_ssl md5)

diff <(openssl md5 Makefile) <(./ft_ssl md5 Makefile)
diff <(openssl md5 author) <(./ft_ssl md5 author)
diff <(openssl md5 ft_ssl) <(./ft_ssl md5 ft_ssl)

diff <(echo "pickle rick" | openssl md5 -r) \
	 <(echo "pickle rick" | ./ft_ssl md5 -r)

diff <(openssl md5 -r Makefile) <(./ft_ssl md5 -r Makefile)
diff <(openssl md5 -r author) <(./ft_ssl md5 -r author)
diff <(openssl md5 -r ft_ssl) <(./ft_ssl md5 -r ft_ssl)

echo 'is md5("salt") a salted hash? :thonking_face:' > tmp
diff <(openssl md5 tmp) <(./ft_ssl md5 tmp)

diff <(echo "Magic mirror on the wall, think I wanna smash them all?" | openssl md5) \
	 <(echo "Magic mirror on the wall, think I wanna smash them all?" | ./ft_ssl md5)

diff <(echo "Speed up now, Gas Pedal??" | openssl md5) \
	 <(echo "Speed up now, Gas Pedal??" | ./ft_ssl md5)

echo "Lorem ipsum dolor amet thundercats letterpress cray
	portland cornhole coloring book twee prism hexagon mixtape pork
	belly hell of four dollar toast disrupt. Hammock PBR&B bicycle
	rights selvage street art, lumbersexual gochujang vegan hot
	chicken. Meggings drinking vinegar biodiesel poke roof party
	tote bag cloud bread ethical. Glossier flannel 8-bit hexagon
	selvage adaptogen farm-to-table offal knausgaard pickled." > tmp

diff <(openssl sha256 tmp) <(./ft_ssl sha256 tmp)
rm -rf tmp

diff <(echo "privet kak dela?" | ./ft_ssl md5 Makefile)\
	 <(openssl md5 Makefile)
