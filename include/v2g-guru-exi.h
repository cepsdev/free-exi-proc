/*
    v2g-guru-exi - an EXI (= "Efficient XML Interchange") processor
    Copyright (C) 2022 Tomas Prerovsky <cepsdev@hotmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "ceps_ast.hh"
#include "core/include/state_machine_simulation_core.hpp"

#include <vector>
#include <queue>
#include <stack>

namespace v2g_guru_exi{
    using namespace ceps::ast;
    using namespace std;
    class Grammar{
        public:
            using grammar_rep_t = node_t;
            using grammar_elem_t = node_t;

            class NonTerminal{
                node_t rep;
                public:
                NonTerminal(grammar_elem_t rep) : rep{rep} {}
                string name() const; 
            };

            class Terminal{

            };

            using lhs_t = node_t;
            using rhs_t = node_t;
            using rhs_vec_t = vector<grammar_elem_t>;
            using lhs_vec_t = vector<NonTerminal>;

        private:
            grammar_rep_t grammar_rep;

            std::optional<NonTerminal> is_lhs(grammar_elem_t) const;

            template<typename F> void foreach_grammar_element(F f) {
                auto& g = as_struct_ref(grammar_rep);
                for(auto p : children(g) ){
                    f(p);
                }
            }
        public:
            Grammar(node_t grammar_rep): grammar_rep{grammar_rep} {}
            lhs_vec_t left_hand_sides();
            rhs_vec_t right_hand_sides(NonTerminal lhs);
    };

    class Event{
        public:

    };

    class EventStream{
        public:
            Event get_event();
    };

    class processor{
        EventStream event_stream;
        stack<Grammar> grammars;
        
        public:
            void set_start_grammar(Grammar g);
            void encode();            
    };

    bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
    bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
}