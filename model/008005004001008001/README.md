<pre>
📎 8.5.4.1.8.1 Sequence ;odel Groups



Given a particle {term} PT_i that is a model group with {compositor} equal to &quot;sequence&quot; and a list of n {particles} P_0, P_1, ... , P_{n-1}, create a grammar ParticleTerm_i as follows:

If the value of n is 0, add the following productions to the grammar ParticleTerm_i.

    ParticleTerm_{i,0}:
        EE

Otherwise, generate a sequence of grammars Particle_0, Particle_1, ..., P_{n-1} corresponding to the list of particles P_0, P_1, ... , P_{n-1} according to section 8.5.4.1.5 Particles. 
Then combine the sequence of grammars using the grammar concatenation operator defined in section 8.5.4.1.5 Particles. Then combine the sequence of grammars using the grammar concatenation
operator defined in section 8.5.4.1.1 Grammar Concatenation operator defined in section 8.5.4.1.1 Grammar Concatenation operator as follows:

    ParticleTerm_i = Particle_0 + Particle_1 + ... + Particle_{n-1}



</pre>


