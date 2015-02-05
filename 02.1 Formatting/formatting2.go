// 2. Done
package main

import (
	"fmt"
)

func main() {
	msg := []byte("Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.")
	fmt.Printf("\nInput : %s\n\nOutput : %s\n\n", string(msg), base64(msg))
}

func base64(inputMsg []byte) string {

	outputMsg := make([]byte, 4*((len(inputMsg)+2)/3))

	for i, j := 0, 0; i < len(inputMsg); i, j = i+3, j+4 {
		for index, element := range getFourBytesFromThree(inputMsg[i:]) {
			outputMsg[j+index] = element
		}
	}

	return string(outputMsg)
}

func getFourBytesFromThree(src []byte) []byte {
	four := []byte{0, 0, 0, 0}
	three := []byte{0, 0, 0}

	switch len(src) {
	case 1:
		three = append(src[0:1], []byte{0, 0}...)
	case 2:
		three = append(src[0:2], 0)
	default:
		three = src[0:3]
	}

	four[0] += three[0] & (1*128 + 1*64 + 1*32 + 1*16 + 1*8 + 1*4 + 0*2 + 0*1) / (2 * 2)

	four[1] += three[0] & (0*128 + 0*64 + 0*32 + 0*16 + 0*8 + 0*4 + 1*2 + 1*1) * (2 * 2 * 2 * 2)
	four[1] += three[1] & (1*128 + 1*64 + 1*32 + 1*16 + 0*8 + 0*4 + 0*2 + 0*1) / (2 * 2 * 2 * 2)

	four[2] += three[1] & (0*128 + 0*64 + 0*32 + 0*16 + 1*8 + 1*4 + 1*2 + 1*1) * (2 * 2)
	four[2] += three[2] & (1*128 + 1*64 + 0*32 + 0*16 + 0*8 + 0*4 + 0*2 + 0*1) / (2 * 2 * 2 * 2 * 2 * 2)

	four[3] += three[2] & (0*128 + 0*64 + 1*32 + 1*16 + 1*8 + 1*4 + 1*2 + 1*1)

	m := []byte{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'}

	switch len(src) {
	case 1:
		return []byte{m[four[0]], m[four[1]], '=', '='}
	case 2:
		return []byte{m[four[0]], m[four[1]], m[four[2]], '='}
	default:
		return []byte{m[four[0]], m[four[1]], m[four[2]], m[four[3]]}
	}
}
