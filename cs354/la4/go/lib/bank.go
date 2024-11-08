package lib

import (
	"fmt"
	"strings"
)

type Bank struct {
	accounts map[string]IAccount
}

func NewBank() (b *Bank) {
	b = new(Bank)
	b.Init()
	return
}

func (b *Bank) Init() {
	b.accounts = make(map[string]IAccount)
}

func (b *Bank) Add(account IAccount) {
	b.accounts[account.String()] = account
}

func (b *Bank) Accrue(rate float64) {
	c := make(chan float64)
	var sum float64 = 0.0
	for _, a := range b.accounts {
		go a.Accrue(c, rate)
	}
	for i := 0; i < len(b.accounts); i++ {
		sum += <- c
	}
	fmt.Printf("Total Accrual: $%.2f\n", sum)
}

func (b *Bank) String() string {
	builder := new(strings.Builder)
	for _, a := range b.accounts {
		builder.WriteString(a.String())
		builder.WriteRune('\n')
	}
	return builder.String()
}
