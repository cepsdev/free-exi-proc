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


namespace v2g_guru_exi{
        class Grammar::Production{
        public:
            class iterator_t;
            struct rhs_elem_t;

            Production() = default;
            Production(NonTerminal lhs, grammar_elem_t rep_rhs) : lhs{lhs}, rep_rhs{rep_rhs} {}
            NonTerminal get_lhs() const {return lhs;}
            grammar_elem_t get_rhs_rep() const {return rep_rhs;}
            size_t size() const { if (rep_rhs ==  nullptr) return 0; return children(as_struct_ref(rep_rhs)).size(); }
            optional<EventCode> get_eventcode();
            bool is_generic(int&) const;
            bool is_generic() const;
            optional<Production> instantiate(Terminal term) const;
            void incr_ev_pos(int delta, int pos);

            iterator_t begin();
            iterator_t end();

            static constexpr int GENERIC_DEFAULT = 0;
            static constexpr int GENERIC_IF_EVCODE_LEN_NOT_ONE = 1;
            static rhs_vec_t empty_vec;

        private:
            NonTerminal lhs{};
            grammar_elem_t rep_rhs{};
    };



    struct Grammar::Production::rhs_elem_t{
                        
        iterator_t* assoc_it{};
        grammar_elem_t rep{};
        rhs_elem_t() = default;
        rhs_elem_t(grammar_elem_t rep): rep{rep} {}
        rhs_elem_t(grammar_elem_t rep,iterator_t* assoc_it):assoc_it{assoc_it}, rep{rep} {}

        bool is_terminal() const;
        bool is_nonterminal() const;        
        bool is_action() const;        
        bool is_annotation() const;
        bool is_eventcode() const;
        Grammar::Terminal as_terminal() const;
        Grammar::NonTerminal as_nonterminal() const;
        Grammar::EventCode as_eventcode() const;
        Grammar::Action as_action() const ;
        rhs_elem_t& operator = (NonTerminal const & rhs );
    };

    class Grammar::Production::iterator_t{
            rhs_vec_t& rep_rhs;
            size_t pos = 0;
        public:
            iterator_t() = delete;
            iterator_t(rhs_vec_t& rep_rhs, size_t pos) : rep_rhs{rep_rhs}, pos{pos} {}

            operator bool() {
                return pos < rep_rhs.size();
            }

            rhs_elem_t operator *() {
                return rhs_elem_t{rep_rhs[pos], this};
            }

            iterator_t& operator ++ () {
                if (pos < rep_rhs.size()) ++pos;
                return *this;
            }

            bool operator == (iterator_t const & rhs) const {
                return pos == rhs.pos;
            }

            bool operator != (iterator_t const & rhs) const {
                return pos != rhs.pos;
            }
            friend class rhs_elem_t;
    };

}