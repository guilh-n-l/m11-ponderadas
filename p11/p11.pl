sintomas([febre,
    tosse,
    dor_de_cabeca,
    fadiga,
    dor_muscular,
    falta_de_ar,
    dor_de_garganta,
    congestao_nasal,
    nausea,
    diarreia,
    perda_de_paladar,
    perda_de_olfato,
    erupcao_cutanea]).

sintoma_pergunta(S, P) :-
    sintomas(Ss),
    member(S, Ss),
    atom_concat('Você está sentindo ', S, P1),
    atom_concat(P1, '?', P).

doencas_sintomas([[gripe, [febre, tosse, dor_de_garganta, fadiga, dor_muscular]],
  [resfriado, [tosse, dor_de_garganta, congestao_nasal]],
  [covid_19, [febre, tosse, falta_de_ar, perda_de_paladar, perda_de_olfato]],
  [alergia, [congestao_nasal, tosse, dor_de_cabeca]],
  [intoxicacao_alimentar, [nausea, diarreia, dor_de_cabeca, fadiga]],
  [dengue, [febre, dor_muscular, fadiga, nausea, erupcao_cutanea]],
  [pneumonia, [febre, tosse, falta_de_ar]]]).

verify_sintomas([]).
verify_sintomas([H|T]) :- (verificar_sintoma(H), !), verify_sintomas(T).

diagnostico(D) :-
    doencas_sintomas(Ds),
    member([D, S], Ds),
    verify_sintomas(S).
