class Heap
{
	void Alloc ( Var & x )
	{
		if ( x . m_Type != Type :: REFERENCE && x . m_Type != Type :: FIELD )
		{
			return;
			//throw runtime_error ( "Cant alloc atomic type." );
		}
		
		vector<Var> & prototype;
	
		if ( x . m_Type == Type :: FIELD )
		{
			x . m_Reference = new vector<Var> (); 
			for ( int i = 0; i < len; i ++ )
			{
				x . push_back ( type );
				m_Heap . push_back ( x . m_Reference );
				
				Alloc ( )
			}
		}
		
		else
		{
			try
			{
				prototype = x . m_Class -> m_ConstantPool -> getMembers ();
			}
			
			catch ( out_of_range & )
			{
				throw runtime_error ( "Cant find prototype." );
			}
				x . m_Reference = new vector<Var> ( prototype ); 
				m_Heap . push_back ( x . m_Reference );
		}		
	} 
	
	private:
	vector<vector<Var>> * m_Heap;
	
}
