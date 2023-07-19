/*
    free-ewxi-proc - an EXI (= "Efficient XML Interchange") processor
    Copyright (C) 2023 Tomas Prerovsky <cepsdev@hotmail.com>

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

namespace v2g_guru_exi{
    class Grammar::Terminal{
        private:
            bool wild_card_uri() const { return !content.uri; }                
            bool wild_card_local_name() const {return !content.local_name;}                
            bool wild_card() const {return wild_card_uri() && wild_card_local_name(); }                
        public:
            struct content_t{
                optional<string_t> uri;
                optional<string_t> prefix;
                optional<string_t> local_name;
                optional<string_t> value;
                optional<string_t> inherited_uri;
                optional<string_t> inherited_name;
            } content;

            Terminal() = default;
            Terminal(grammar_elem_t rep_arg) {
                if ( 
                    rep_arg && 
                    is<Ast_node_kind::symbol>(rep_arg) && 
                    kind(as_symbol_ref(rep_arg)) == "GrammarTerminal" ) 
                 rep = rep_arg;
                else if (
                    rep_arg && 
                    is<Ast_node_kind::func_call>(rep_arg) && 
                    is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(rep_arg))) && 
                    kind(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg)))) == "GrammarTerminal"  ) 
                 rep = rep_arg;
                else rep = nullptr;
            }
            bool valid() const { return rep != nullptr;}
            grammar_elem_t get_rep() const {return rep;}
            string as_str() const;
            string name() const;
            void set_name(string);
            optional<content_t> get_content() const;
        private:
            grammar_elem_t rep{};

    };
}
