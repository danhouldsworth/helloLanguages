// 2. Done.
/*
Great follow on from blog on encoding UTF8 / unicode : http://blog.golang.org/strings
"To summarize, strings can contain arbitrary bytes, but when constructed from string literals, those bytes are (almost always) UTF-8."
String elements are runes (or unicode code points). Need to be clear on this when iterating over strings.
*/

package main

import (
	"bytes"
	"fmt"
)

var (
	greeting = "The quick brown 狐 jumped over the lazy 犬!"
	buffer   = bytes.NewBuffer(nil)
)

func main() {
	for _, runeValue := range greeting {
		buffer.WriteRune(runeValue)
		fmt.Println(buffer)
	}
}
