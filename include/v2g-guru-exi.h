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
                grammar_elem_t rep{};
                public:
                NonTerminal() = default;
                NonTerminal(grammar_elem_t rep) : rep{rep} {}
                string name() const;
                grammar_elem_t get_rep() const {return rep;} 
            };

            class Terminal{
                grammar_elem_t rep{};
                public:
                    Terminal() = default;
                    Terminal(grammar_elem_t rep_arg) {
                        if ( rep_arg && is<Ast_node_kind::symbol>(rep_arg) && kind(as_symbol_ref(rep_arg)) == "GrammarTerminal" ) rep = rep_arg;
                    }
                    bool valid() const { return rep != nullptr;}
                    grammar_elem_t get_rep() const {return rep;}
            };

            class Production{
                NonTerminal lhs{};
                grammar_elem_t rep_rhs{};
                public:
                    Production() = default;
                    Production(NonTerminal lhs, grammar_elem_t rep_rhs) : lhs{lhs}, rep_rhs{rep_rhs} {}
                    NonTerminal get_lhs() {return lhs;}
                    grammar_elem_t get_rhs_rep() {return rep_rhs;}
            };

            using lhs_t = node_t;
            using rhs_t = node_t;
            using rhs_vec_t = vector<grammar_elem_t>;
            using lhs_vec_t = vector<NonTerminal>;

        private:
            grammar_rep_t grammar_rep{};

            std::optional<NonTerminal> is_lhs(grammar_elem_t) const;

            template<typename F> void foreach_grammar_element(F f) {
                auto& g = as_struct_ref(grammar_rep);
                for(auto p : children(g) ){
                    f(p);
                }
            }
            template<typename F> void foreach_grammar_element_until(F f) {
                auto& g = as_struct_ref(grammar_rep);
                for(auto p : children(g) ){
                    if(!f(p)) return;
                }
            }
        public:
            Grammar(node_t grammar_rep): grammar_rep{grammar_rep} {}
            lhs_vec_t left_hand_sides();
            rhs_vec_t right_hand_sides(NonTerminal lhs);
            optional<Production> find_production_starting_with(Terminal);
    };

    class Event {
        public:
            using event_rep_t = node_t;
            Event() = default;
            Event(event_rep_t);
            operator bool(){
                return valid;
            }
            Grammar::Terminal as_terminal() const { return Grammar::Terminal{ev_rep}; }
            bool is_SD();
            event_rep_t get_rep() { return ev_rep;}
        private:
            event_rep_t ev_rep{};
            bool valid{};
    };

    class EventStream{      
        public:
            using event_stream_rep_t = std::vector<node_t>;
            EventStream() = default;
            explicit EventStream(event_stream_rep_t);
            Event get_event();
            operator bool() {return ev_stream_rep.size() > next_ev_idx; }
        private:
            event_stream_rep_t ev_stream_rep;
            size_t next_ev_idx = 0;
    };

    class Processor{
        EventStream event_stream;
        stack<Grammar> grammars;
        public:
            Processor() = default;
            void set_start_grammar(Grammar g);
            void set_event_stream(EventStream ev_stream);
            void encode();            
    };

    bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
    bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
    bool operator == (Grammar::Terminal const &, Grammar::Terminal const & );
}