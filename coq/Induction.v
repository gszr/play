Require Export Basics.

(* Try proving that 0 is a neutral element for + on the right *)

Theorem plus_n_O_firsttry: forall n: nat, n = n + 0.
Proof.
  intros n.
  simpl.
Abort.

Theorem plus_n_O_secondtry: forall n: nat, n = n + 0.
Proof.
  intros [|n'].
  - reflexivity.
  - simpl. destruct n' as [|n''].
Abort.

(* 
  Neither of these work because n in n + 0 is an arbitrary natural
  number. Here we need to use a stronger proof method:
  
    (Induction) To prove some proposition P(n), where n is a natural
    number, we need to show that P holds for all natural numbers n:
      Base: P(O) holds
      Inductive step: for any n', P(n') -> P(S n')

*)

Theorem plus_n_O: forall n: nat, n = n + 0.
Proof.
  intros n. induction n as [| n' IHn'].
  - reflexivity.
  - simpl. rewrite <- IHn'. reflexivity.
Qed.

Theorem minus_diag: forall n: nat, minus n n = 0.
Proof.
  induction n as [| n' IHn'].
  - reflexivity.
  - simpl. rewrite -> IHn'. reflexivity.
Qed.

(* Some exercises *)

Theorem mult_0_r: forall n: nat, n * 0 = 0.
Proof.
  induction n as [| n' IHn'].
  - reflexivity.
  - simpl. rewrite -> IHn'. reflexivity.
Qed.

Theorem plus_n_Sm: forall n m: nat, S (n + m) = n + (S m).
Proof.
  induction n as [| n' IHn'].
  - intros. simpl. reflexivity.
  - intros. simpl. rewrite -> IHn'. reflexivity.
Qed.

Theorem plus_comm: forall n m: nat, n + m = m + n.
Proof.
  induction n as [| n' IHn'].
  - simpl. apply plus_n_O.
  - intros m. simpl. rewrite -> IHn'. apply plus_n_Sm.
Qed.

Theorem plus_assoc: forall n m p: nat, n + (m + p) = (n + m) + p.
Proof.
  induction n as [| n' IHn'].
  - intros m p. simpl. reflexivity.
  - intros m p. simpl. rewrite -> IHn'. reflexivity.
Qed.

Fixpoint double (n: nat) :=
  match n with
  | O => O
  | S n' => S (S (double n'))
  end.

Lemma double_plus: forall n, double n = n + n.
Proof.
  induction n as [| n' IHn'].
  - reflexivity.
  - simpl. rewrite -> IHn'. rewrite <- plus_n_Sm. reflexivity.
Qed.

Lemma double_neg: forall n: bool, negb (negb n) = n.
Proof.
  destruct n as [|n'].
  - reflexivity.
  - reflexivity.
Qed.

Theorem evenb_S: forall n: nat, evenb (S n) = negb (evenb n).
Proof.
Abort.

(* Using assert tactics to state intermediary facts in a proof *)

Theorem mult_O_plus: forall n m: nat, (0 + n) * m = n * m.
Proof.
  intros n m.
  assert (0 + n = n) as H. { reflexivity. }
  rewrite -> H.
  reflexivity.
Qed.

(*
  Sometimes, to prove certain things, we need to reuse past proofs,
  but the rewrite tactics isn't always smart enough to figure out
  where to rewrite:
*)

Theorem plus_rearrange_firsttry: forall n m p q: nat,
  (n + m) + (p + q) = (m + n) + (p + q).
Proof.
  intros n m p q.
  rewrite -> plus_comm.
  (* doesn't work *)
Abort.

(*
  In this case, we need to introduce a local lemma, prove it using
  the past proof, and use the lemma:
*)

Theorem plus_rearrange: forall n m p q: nat,
  (n + m) + (p + q) = (m + n) + (p + q).
Proof.
  intros n m p q.
  assert (H: n + m = m + n). { rewrite -> plus_comm. reflexivity. }
  rewrite -> H.
  reflexivity.
Qed.



















