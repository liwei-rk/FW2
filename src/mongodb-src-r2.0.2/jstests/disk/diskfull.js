doIt = false;
dbpath = "/data/db/diskfulltest";

files = listFiles( "/data/db" );
for ( i in files ) {
    if ( files[ i ].name == dbpath ) {
        doIt = true;
    }
}

if ( !doIt ) {
    print( "path " + dbpath + " missing, skipping diskfull test" );
    doIt = false;
}

if ( doIt ) {
    // Clear dbpath without removing and recreating diskfulltest directory, as resetDbpath does
    files = listFiles( dbpath );
    files.forEach( function( x ) { removeFile( x.name ) } );
    
    port = allocatePorts( 1 )[ 0 ];
    m = startMongoProgram( "mongod", "--port", port, "--dbpath", dbpath, "--nohttpinterface", "--bind_ip", "127.0.0.1" );
    d = m.getDB( "diskfulltest" );
    c = d.getCollection( "diskfulltest" );
    c.save( { a: 6 } );
    assert.eq(d.getLastError(), "new file allocation failure"); // first fail
    assert.soon( function() { return rawMongoProgramOutput().match( /file allocation failure/ ); }, "didn't see 'file allocation failure'" );
    assert.isnull( c.findOne() , "shouldn't exist" );
    c.save( { a: 6 } );
    assert.eq(d.getLastError(), "Can't take a write lock while out of disk space"); // every following fail


    sleep( 3000 );
    m2 = new Mongo( m.host );
    printjson( m2.getDBs() );
}
