import logging
logger = logging.getLogger(__name__)

MAX7219_COUNT = 12

def wait_ready(com):
    last_line = com.readline().strip()
    while last_line <> "READY":
        if not last_line:
            raise Exception("no data")
        logger.debug("'%s'" % last_line)
        last_line = com.readline().strip()
        
    logger.debug("'%s'" % last_line)