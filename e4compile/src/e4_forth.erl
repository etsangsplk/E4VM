-module(e4_forth).

%% API
-export([forth_and/1, forth_if/2, forth_if/3, forth_tuple/1,
         forth_compare/2, forth_literal/1]).

-include_lib("compiler/src/core_parse.hrl").
-include("e4.hrl").

%% Takes list of Forth checks and creates forth instructions which produce
%% true if all conditions are true
%% Assumption: each Cond in Conds is a Forth sequence which leaves one value on stack
forth_and([]) -> [];
forth_and(Conds) ->
    %% Remove true clauses
    Conds1 = lists:filter(
        fun(#c_literal{val='true'}) -> false;
            ([]) -> false;
            (_) -> true
        end,
        Conds),
    case Conds1 of
        [] -> [];
        _ -> [Conds1, lists:duplicate(length(Conds1) - 1, 'AND')]
    end.

forth_if(#e4lit{val='true'}, Body) -> Body;
forth_if(Cond, Body) ->
    [?Lazy(Cond), 'IF', ?Lazy(Body), 'THEN'].

forth_if(Cond, Body, Else) ->
    [?Lazy(Cond), 'IF', ?Lazy(Body), 'ELSE', ?Lazy(Else), 'THEN'].

%% Takes list of Forth expressions where each leaves one value on stack
%% and constructs a tuple of that size
forth_tuple(Values) ->
    [lists:reverse(Values), length(Values), 'MAKE-TUPLE'].

forth_compare(Lhs, Rhs) ->
    [Lhs, Rhs, '=='].

forth_literal(Value) -> #e4lit{val=Value}.
