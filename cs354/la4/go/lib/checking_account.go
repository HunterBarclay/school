package lib

type ICheckingAccount interface {
	IAccount
}

type CheckingAccount struct {
	Account
}

func NewCheckingAccount(number string, customer *Customer, balance float64) (ca *CheckingAccount) {
	ca = new(CheckingAccount)
	ca.Init(number, customer, balance)
	return
}

func (ca *CheckingAccount) Init(number string, customer *Customer, balance float64) {
	ca.number = number
	ca.customer = customer
	ca.balance = balance
}

func (ca *CheckingAccount) Accrue(c chan float64, _ float64) {
	c <- 0
}
