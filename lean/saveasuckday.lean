#eval 1 + 2
#eval 2 + 5
#eval String.append "Hello, " "Lean!"
#eval String.append "great " (String.append "oak " "tree")
#eval String.append "it is " (if 1 > 2 then "yes" else "no")
#eval (1 - 2 : Int)
#check (1 - 2)
def lean : String := "Lean"
theorem add_comm_induction (x y : Nat) : x + y = y + x := by
  induction x with
  | zero =>
      -- base case: x = 0
      simp
  | succ x ih =>
      -- induction step: assume x + y = y + x
      -- goal: (x+1) + y = y + (x+1)
      rw[Nat.add_succ, Nat.add_zero, Nat.add_succ, Nat.succ_add, ih]
