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
            string global_id_{};
            bool modifiable_{true};
        public:
            class NonTerminal;
            class Terminal;
            class Action;
            class EventCode;
            class Production;

            using grammar_rep_t = node_t;
            using grammar_elem_t = node_t;
            using lhs_t = node_t;
            using rhs_t = node_t;
            using rhs_vec_t = vector<grammar_elem_t>;
            using grammar_pattern_rep_t = grammar_rep_t;
            using lhs_vec_t = vector<NonTerminal>;
            using sorted_vec_of_unique_nonterminals_t = vector<NonTerminal>; 
            using vec_pairs_of_nonterminals_t = vector<pair<NonTerminal,NonTerminal>>; 
            
            
            grammar_rep_t grammar_rep{};

            bool has_global_id() const {return global_id_.length() > 0;}
            string global_id() const {return global_id_;}
            string& global_id()  {return global_id_;}
            bool is_modifiable() const {return modifiable_;}
            bool& modifiable()  {return modifiable_;}           
            std::optional<NonTerminal> is_lhs(grammar_elem_t) const;
            std::optional<Production> is_rhs(grammar_elem_t) const;

            template<typename F>  void foreach_grammar_element(F f) const {
                auto& g = as_struct_ref(grammar_rep);
                for(auto p : children(g) ){
                    f(p);
                }
            }
            template<typename F>  void foreach_grammar_element_until(F f) const {
                auto& g = as_struct_ref(grammar_rep);
                for(auto p : children(g) ){
                    if(!f(p)) return;
                }
            }
            Grammar() = default;
            Grammar(node_t grammar_rep): grammar_rep{grammar_rep} {}
            Grammar(Grammar const & g){
                if (!g.grammar_rep) grammar_rep = nullptr;
                else grammar_rep = g.grammar_rep->clone();
                global_id_ = g.global_id_;
                modifiable_ = g.modifiable_;   
            }

            lhs_vec_t left_hand_sides();
            vector<Production> right_hand_sides(NonTerminal lhs);
            optional<Production> find_production_starting_with(Terminal);
            void insert(Production prod);
            bool rename_non_termial(string from , string to);
            bool rename_terminal_to_nonterminal(string from , string to);
            sorted_vec_of_unique_nonterminals_t get_lhs_nonterminals() const;
            sorted_vec_of_unique_nonterminals_t get_all_nonterminals() const;
            sorted_vec_of_unique_nonterminals_t confliciting_nonterminals(Grammar const & g) const;
            vec_pairs_of_nonterminals_t resolve_conflicting_nonterminals(Grammar const & g) const;
    };

    class GenericGrammar{
        Grammar g = {};
        Grammar::grammar_pattern_rep_t pattern = {};
        mutable bool pattern_str_cache_valid {false};
        string pattern_str_cache;
        public:
        GenericGrammar() = default;
        GenericGrammar(Grammar::grammar_elem_t);
        string pattern_to_str();
        Grammar get_grammar() const {return g;}        
    };

    class Event {
        public:
            using event_rep_t = node_t;
            Event() = default;
            Event(event_rep_t);
            operator bool(){
                return valid;
            }
            Grammar::Terminal as_terminal() const;
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
            Event peek();
            operator bool() {return ev_stream_rep.size() > next_ev_idx; }
        private:
            event_stream_rep_t ev_stream_rep;
            size_t next_ev_idx = 0;
    };

    class Emitter{ 
        public:
        virtual void emit(Grammar::EventCode) = 0;
    };

    class ceps_emitter: public Emitter {
        node_t encoding_result{};
        public:
        ceps_emitter(node_t encoding_result):encoding_result{encoding_result}{}
        void emit(Grammar::EventCode) override;
    };

    class Processor{
        EventStream event_stream;
        stack<Grammar> grammars;
        map<string,Grammar> global_grammars;
        map<string,Grammar> generic_grammars;
        bool debug_output = false;
        bool debug_output_emit_eventcode = true;        
        bool match(Grammar::Terminal);
        //Well, yes we use runtime polymorphism refraining from type parametrization in this case (sometimes i surprise myself). 
        Emitter* emitter{};
        public:
            struct parser_exception{std::string msg;};
            Processor() = default;
            void set_start_grammar(Grammar g);
            void set_event_stream(EventStream ev_stream);
            void encode();
            void parse(Grammar g);
            bool parse(Grammar g, Grammar::Production prod);
            void insert(GenericGrammar);
            void emit_eventcode(Grammar& g, Grammar::Production prod);
            void set_emitter(Emitter* an_emitter) {emitter = an_emitter;}
    };

 
    class Grammar::NonTerminal{       
        public:
            NonTerminal() = default;
            NonTerminal(grammar_elem_t rep) : rep{rep} {}
            NonTerminal(string name);
            string name() const;
            void set_name(string);
            grammar_elem_t get_rep() const {return rep;}
        private:
            grammar_elem_t rep{};
 
    };
    
    class Grammar::Terminal{                
        public:
            Terminal() = default;
            Terminal(grammar_elem_t rep_arg) {
                if ( rep_arg && is<Ast_node_kind::symbol>(rep_arg) && kind(as_symbol_ref(rep_arg)) == "GrammarTerminal" ) rep = rep_arg;
                else if (rep_arg && is<Ast_node_kind::func_call>(rep_arg) && is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(rep_arg))) && 
                        kind(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg)))) == "GrammarTerminal"  ) rep = rep_arg;
                else rep = nullptr;
            }
            bool valid() const { return rep != nullptr;}
            grammar_elem_t get_rep() const {return rep;}
            string as_str() const;
            string name() const;
            void set_name(string);
        private:
            grammar_elem_t rep{};
    };
    
    class Grammar::Action{
            grammar_elem_t rep{};
            string action_name_;
        public:
            Action() = default;            
            Action(grammar_elem_t rep_arg) {
                        if ( rep_arg && is<Ast_node_kind::symbol>(rep_arg) && kind(as_symbol_ref(rep_arg)) == "GrammarAction" ) {
                            rep = rep_arg;
                            action_name_ = name(as_symbol_ref(rep_arg));
                        } else if (rep_arg && is<Ast_node_kind::func_call>(rep_arg) && is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(rep_arg))) && 
                                kind(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg)))) == "GrammarAction"  ) {
                                    rep = rep_arg;
                                    action_name_ = name(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg))));
                        }
                        else rep = nullptr;
                    }
            bool valid() const { return rep != nullptr;}
            grammar_elem_t get_rep() const {return rep;}
            string action_name() const { return action_name_; }
    };

    class Grammar::EventCode{
            grammar_elem_t rep{};
            grammar_elem_t code_rep[3] = {nullptr, nullptr, nullptr};
        public:
            int code[3] = {0,0,0};
            int dim = 0;
            EventCode() = default;
            EventCode(grammar_elem_t rep_arg){
                    if(!rep_arg) return;
                    string func_id;
                    std::vector<node_t> args;
                    if (!is_a_simple_funccall(  rep_arg,
				                                func_id,
                                                args)) return;
                    if (func_id != "EventCode") return;
                    dim = args.size();
                    size_t j = 0;
                    for (size_t i = 0; i < args.size(); ++i)
                        if (is<Ast_node_kind::int_literal>(args[i]))
                            code[min(j++,2UL)] = value(as_int_ref(code_rep[i] = args[i]));
                    rep = rep_arg;
            }
            bool valid() const{ return rep != nullptr;}
            grammar_elem_t* get_code_rep() {return code_rep;}
    };
    
    bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
    bool operator < (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);

    bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs);
    bool operator == (Grammar::Terminal const &, Grammar::Terminal const & );
    ostream& operator << (ostream& os, Grammar::EventCode const &);
    ostream& operator << (ostream& os, Grammar::Production );
    ostream& operator << (ostream& os, Grammar );
    ostream& operator << (ostream& os, Grammar::NonTerminal );
    ostream& operator << (ostream& os, Grammar::Terminal );
    bool operator <= (Grammar::EventCode lhs, Grammar::EventCode rhs); 

}

#include "v2g-guru-exi-grammar-prod.h"