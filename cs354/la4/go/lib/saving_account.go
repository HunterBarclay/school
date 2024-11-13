package lib

/*
Savings accounts that support interest accrual.
*/

type ISavingAccount interface {
	IAccount
}

type SavingAccount struct {
	Account
	interest float64
}

func NewSavingAccount(number string, customer *Customer, balance float64) (s *SavingAccount) {
	s = new(SavingAccount)
	s.Init(number, customer, balance)
	return
}

func (s *SavingAccount) Init(number string, customer *Customer, balance float64) {
	s.number = number
	s.customer = customer
	s.balance = balance
}

func (s *SavingAccount) Accrue(c chan float64, rate float64) {
	interest := s.balance * rate
	s.interest += interest
	s.balance += interest
	c <- interest
}
