(* Coq Basics *)

(* ***************** TYPES AND FUNCTIONS *****************)

(* days type *)
Inductive day : Type :=
  | monday : day
  | tuesday : day
  | wednesday : day
  | thursday : day
  | friday : day
  | saturday : day
  | sunday : day.

(* next_weekday function *)
Definition next_weekday (d:day) : day :=
  match d with
  | monday => tuesday
  | tuesday => wednesday
  | wednesday => thursday
  | thursday => friday
  | friday => monday
  | saturday => monday
  | sunday => monday
  end.

(* Test next_weekday *)
Compute (next_weekday friday).

(* Define an example and prove it *)
Example test_next_weekday: next_weekday (next_weekday saturday) = tuesday.
Proof. simpl. reflexivity. Qed.

(******************* LOGIC *****************)

(* boolean type *)
Inductive bool: Type :=
  | true: bool
  | false: bool.

(* NOT boolean function *)
Definition negb (b: bool): bool :=
  match b with
  | true => false
  | false => true
  end.

(* AND boolean function *)
Definition andb (b1: bool) (b2: bool): bool :=
  match b1 with
  | true => b2
  | false => false
  end.

(* OR boolean function *)
Definition orb (b1: bool) (b2: bool): bool :=
  match b1 with
  | true => true
  | false => b2
  end.

(* tests (truth table) for the OR function *)
Example test_orb1: (orb true false) = true.
Proof. simpl. reflexivity. Qed.
Example test_orb2: (orb false false) = false.
Proof. simpl. reflexivity. Qed.
Example test_orb3: (orb false true) = true.
Proof. simpl. reflexivity. Qed.
Example test_orb4: (orb true true) = true.
Proof. simpl. reflexivity. Qed.

(* Infix operators *)
Infix "&&" := andb.
Infix "||" := orb.

Example test_orb5: false || false || true = true.
Proof. simpl. reflexivity. Qed.

(* NAND *)
Definition nandb (b1: bool) (b2: bool): bool :=
  match andb b1 b2 with
  | true => false
  | false => true
  end.

(* tests (truth table) for the NAND function *)
Example test_nandb1: (nandb true false) = true.
Proof. simpl. reflexivity. Qed.
Example test_nandb2: (nandb false false) = true.
Proof. simpl. reflexivity. Qed.
Example test_nandb3: (nandb false true) = true.
Proof. simpl. reflexivity. Qed.
Example test_nandb4: (nandb true true) = false.
Proof. simpl. reflexivity. Qed.

(* 3-args AND *)
Definition andb3 (b1: bool) (b2: bool) (b3: bool): bool :=
  andb (andb b1 b2) b3.

(* some tests for the 3-args AND function *)
Example test_andb31: (andb3 true true true) = true.
Proof. simpl. reflexivity. Qed.
Example test_andb32: (andb3 false true true) = false.
Proof. simpl. reflexivity. Qed.
Example test_andb33: (andb3 true false true) = false.
Proof. simpl. reflexivity. Qed.
Example test_andb34: (andb3 true true false) = false.
Proof. simpl. reflexivity. Qed.

Check andb.
Check andb3.

(*******************************************)
(*******************************************)

(******************* NUMBERS *****************)

Module NatNumbers.

Inductive nat : Type :=
  | O: nat
  | S: nat -> nat.

Definition pred (n: nat): nat :=
  match n with
  | O => O
  | S n' => n'
  end.

End NatNumbers.

(* a number minus two *)
Definition minustwo (n: nat): nat :=
  match n with
  | O => O
  | S O => O
  | S (S n') => n'
  end.

Check (S (S (S (S O)))).
Check minustwo.
Check 4.

(* is a number even? *)
Fixpoint evenb (n: nat): bool :=
  match n with
  | O => true
  | S O => false
  | S (S n') => evenb n'
  end.

Compute (evenb (S(S O))).
Compute (evenb 0).
Compute (evenb 2).

Example test_evenb1: evenb 0 = true.
Proof. simpl. reflexivity. Qed.
Example test_evenb2: evenb 1 = false.
Proof. simpl. reflexivity. Qed.
Example test_evenb3: evenb 2 = true.
Proof. simpl. reflexivity. Qed.

(* is a number odd? *)
Definition oddb (n: nat): bool := negb (evenb n).

Example test_oddb1: oddb 1 = true.
Proof. simpl. reflexivity. Qed.
Example test_oddb2: oddb 3 = true.
Proof. simpl. reflexivity. Qed.
Example test_oddb3: oddb 4 = false.
Proof. simpl. reflexivity. Qed.

Fixpoint plus (n m: nat): nat :=
  match n with
  | O => m
  | S n' => S(plus n' m)
  end.

Example test_plus1: (plus 3 3) = 6.
Proof. simpl. reflexivity. Qed.

(* mult function *)
Fixpoint mult (n m: nat): nat :=
  match n with
  | O => O
  | S n' => plus m (mult n' m)
  end.

(* mult function tests *)
Example test_mult1: (mult 3 3) = 9.
Proof. simpl. reflexivity. Qed.

(* minus function *)
Fixpoint minus (n m: nat): nat :=
  match n, m with
  | O , _ => O
  | _ , O => n
  | S n', S m' => minus n' m'
  end.

(* minus function tests *)
Example test_minus1: (minus 2 3) = 0.
Proof. simpl. reflexivity. Qed.
Example test_minus2: (minus 3 3) = 0.
Proof. simpl. reflexivity. Qed.
Example test_minus3: (minus 4 3) = 1.
Proof. simpl. reflexivity. Qed.
Example test_minus4: (minus 5 3) = 2.
Proof. simpl. reflexivity. Qed.

(* exp function *)
Fixpoint exp (base power: nat): nat :=
  match power with
  | O => S O
  | S p => mult base (exp base p)
  end.

(* exp function tests *)
Example test_exp1: (exp 3 0) = 1.
Proof. simpl. reflexivity. Qed.
Example test_exp2: (exp 3 1) = 3.
Proof. simpl. reflexivity. Qed.
Example test_exp3: (exp 3 2) = 9.
Proof. simpl. reflexivity. Qed.
Example test_exp4: (exp 3 3) = 27.
Proof. simpl. reflexivity. Qed.

(* factorial function *)
Fixpoint fact (n: nat): nat :=
  match n with
  | O => 1
  | S n => mult (S n) (fact (n))
  end.

Example test_fact1: (fact 3) = 6.
Proof. simpl. reflexivity. Qed.
Example test_fact2: (fact 5) = (mult 10 12).
Proof. simpl. reflexivity. Qed.

(* new symbolic notation for some operations *)
Infix "+" := plus.
Infix "-" := minus.
Infix "*" := mult.

(*
  alternative way to define new notations
  level, associativity, and nat_scope control how these
  notations are interpreted by Coq's parser
*)
Notation "x + y" := (plus x y)
                       (at level 50, left associativity)
                       : nat_scope.
Notation "x - y" := (minus x y)
                       (at level 50, left associativity)
                       : nat_scope.
Notation "x * y" := (mult x y)
                       (at level 40, left associativity)
                       : nat_scope.

Compute 2 + 2.
Compute 4 - 2.
Compute 6 * 6.

(* natural equality function *)
Fixpoint beq_nat (n m: nat): bool :=
  match n, m with
  | O, O => true
  | O, _ => false
  | S n', S m' => beq_nat n' m'
  | _, O => false
  end.

(* natural equality function tests *)
Example test_beq_nat1: (beq_nat 0 0) = true.
Proof. simpl. reflexivity. Qed.
Example test_beq_nat2: (beq_nat 1 1) = true.
Proof. simpl. reflexivity. Qed.
Example test_beq_nat3: (beq_nat 1 2) = false.
Proof. simpl. reflexivity. Qed.
Example test_beq_nat4: (beq_nat 10 12) = false.
Proof. simpl. reflexivity. Qed.

(* natural <= function *)
Fixpoint leb (n m: nat): bool :=
  match n, m with
  | O, _ => true
  | S n', O => false
  | S n', S m' => leb n' m'
  end.

(* natural <= function tests *)
Example test_leb1: (leb 2 2) = true.
Proof. simpl. reflexivity. Qed.
Example test_leb2: (leb 2 4) = true.
Proof. simpl. reflexivity. Qed.
Example test_leb3: (leb 4 2) = false.
Proof. simpl. reflexivity. Qed.

(* natural < function *)
Definition blt_nat (n m: nat): bool :=
  andb (negb (beq_nat n m)) (leb n m).

(* natural < function tests*)
Example test_blt_nat1: (blt_nat 2 2) = false.
Proof. simpl. reflexivity. Qed.
Example test_blt_nat2: (blt_nat 2 4) = true.
Proof. simpl. reflexivity. Qed.
Example test_blt_nat3: (blt_nat 4 2) = false.
Proof. simpl. reflexivity. Qed.

(***************** PROOF by SIMPLIFICATION *****************)

(*
  All examples so far were proved using `simpl` and `reflexivity`;
  these tactics are used to simplify expressions and to check that
  both sides contain identical values, respectively
*)

Theorem plus_0_n: forall n: nat, 0 + n = n.
Proof. intros n. simpl. reflexivity. Qed.

(*
  `reflexivity` itself is able to make some simplifications, but
  while they are implicit, `simpl` makes them visible, helping us
  track the state of the proof
*)

Theorem plus_1_l: forall n: nat, 1 + n = S n.
Proof. intros n. simpl. reflexivity. Qed.

(*
  Keywords `Example`, `Theorem`, `Lemma`, `Fact`, and `Remark` all
  mean the same thing in Coq
*)

Theorem mult_0_l: forall n: nat, 0 * n = 0.
Proof. intros n. simpl. reflexivity. Qed.

Theorem plus_n_O : forall n, n = n + 0.
Proof.
  intros n. simpl. (* Doesn't do anything! *) Abort.

(***************** PROOF by REWRITING *****************)

Theorem plus_id_example : forall n m:nat,
  n = m -> n + n = m + m.
Proof. intros n m. intros H. rewrite -> H. reflexivity. Qed.

(*
  Having assumed `n = m`, rewrite allows rewriting the goal
  with a given hypothesis
*)

Theorem plus_id_exercise : forall n m o : nat,
  n = m -> m = o -> n + m = m + o.
Proof. intros n m o. intros H. intros H'. rewrite -> H.
  rewrite H'. reflexivity. Qed.

(*
  Rewrite can also be used to apply a previously proved result
  instead of a hypothesis in the current context. For instance:
*)

Theorem mult_0_plus1: forall n m: nat, (0 + n) * m = n * m.
Proof. intros n m. simpl. reflexivity. Qed.

Theorem mult_0_plus2: forall n m: nat, (0 + n) * m = n * m.
Proof. intros n m. rewrite -> plus_0_n. reflexivity. Qed.

Theorem mult_S_1 : forall n m : nat, m = S n -> m * (1 + n) = m * m.
Proof. intros n m. intros H. simpl. rewrite <- H. reflexivity. Qed.

(***************** PROOF by CASE ANALYSIS *****************)

Theorem plus_1_neq_0_firsttry : forall n: nat, beq_nat (n + 1) 0 = false.
Proof. intros n. simpl. Abort. (* oops... not gonna work *)

Theorem plus_1_neq_0: forall n: nat, beq_nat (n + 1) 0 = false.
Proof.
  intros n.
  destruct n as [| n'].
    -simpl. reflexivity.
    -simpl. reflexivity.
Qed.

(*
  The `destruct` tactic is used to break a goal that involves an
  inductive data type into subgoals, considering each possible case
  separately
*)

Theorem negb_involutive: forall b: bool, negb (negb b) = b.
Proof.
  intros b.
  destruct b.
    - simpl. reflexivity.
    - simpl. reflexivity.
Qed.

Theorem andb_commutative: forall b c: bool, andb b c = andb c b.
Proof.
  intros b c.
  destruct b.
    - destruct c.
      + reflexivity.
      + reflexivity.
    - destruct c.
      + reflexivity.
      + reflexivity.
Qed.

Theorem andb3_exchange:
  forall b c d, andb (andb b c) d = andb (andb b d) c.
Proof.
  intros b c d.
  destruct b.
    - destruct c.
        * destruct d.
            + reflexivity.
            + reflexivity.
        * destruct d.
            + reflexivity.
            + reflexivity.
    - destruct c.
        * destruct d.
            + reflexivity.
            + reflexivity.
        * destruct d.
            + reflexivity.
            + reflexivity.
Qed.

(*
  Variables can be introduced and destructed in a single step by
  using an introduction pattern instead of a variable name
*)

Theorem plus_1_neq_0': forall n: nat, beq_nat (n + 1) 0 = false.
Proof.
  intros [|n].
    - reflexivity.
    - reflexivity.
Qed.

Theorem andb_commutative'': forall b c, andb b c = andb c b.
Proof.
  intros [] [].
    - reflexivity.
    - reflexivity.
    - reflexivity.
    - reflexivity.
Qed.

Theorem andb_true_elim2 : forall b c : bool, andb b c = true -> c = true.
Proof.
  intros b c.
  destruct b.
    - destruct c.
        * reflexivity.
        * simpl. intros H. rewrite -> H. reflexivity.
    - destruct c.
        * simpl. intros H. reflexivity.
        * simpl. intros H. rewrite -> H. reflexivity.
Qed.

Theorem zero_nbeq_plus_1 : forall n : nat, beq_nat 0 (n + 1) = false.
Proof.
  intros n.
  destruct n as [|n'].
    - simpl. reflexivity.
    - simpl. reflexivity.
Qed.
























